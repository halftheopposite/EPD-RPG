// Local storage handling for the tilemap editor
import { EditorState, defaultEditorState } from "./models";

const STORAGE_KEY = "epd-rpg-tilemap-editor";
const SPRITESHEET_KEY = `${STORAGE_KEY}-spritesheet`;
const SPRITESHEET_DATA_KEY = `${STORAGE_KEY}-spritesheet-data`;
const SIDEBAR_WIDTH_KEY = `${STORAGE_KEY}-sidebar-width`;

// Save the spritesheet as a data URL
export async function saveSpritesheetToStorage(file: File): Promise<string> {
  return new Promise((resolve, reject) => {
    const reader = new FileReader();
    reader.onload = () => {
      try {
        const dataUrl = reader.result as string;
        localStorage.setItem(SPRITESHEET_KEY, dataUrl);

        // Save spritesheet metadata
        const spritesheetData = {
          filename: file.name,
          lastModified: file.lastModified,
          size: file.size,
          type: file.type,
        };
        localStorage.setItem(
          SPRITESHEET_DATA_KEY,
          JSON.stringify(spritesheetData)
        );

        resolve(dataUrl);
      } catch (error) {
        console.error("Failed to save spritesheet:", error);
        reject(error);
      }
    };
    reader.onerror = () => reject(new Error("Failed to read spritesheet file"));
    reader.readAsDataURL(file);
  });
}

// Load the spritesheet from storage
export async function loadSpritesheetFromStorage(): Promise<{
  image: HTMLImageElement;
  filename: string;
} | null> {
  const dataUrl = localStorage.getItem(SPRITESHEET_KEY);
  const spritesheetDataJson = localStorage.getItem(SPRITESHEET_DATA_KEY);

  if (!dataUrl || !spritesheetDataJson) return null;

  try {
    const spritesheetData = JSON.parse(spritesheetDataJson);
    const image = new Image();
    image.src = dataUrl;

    // Wait for the image to load
    await new Promise<void>((resolve, reject) => {
      image.onload = () => resolve();
      image.onerror = () =>
        reject(new Error("Failed to load spritesheet image"));
    });

    return {
      image,
      filename: spritesheetData.filename || "spritesheet.png",
    };
  } catch (error) {
    console.error("Failed to load spritesheet from storage:", error);
    return null;
  }
}

// Save editor state to localStorage
export async function saveEditorState(state: EditorState): Promise<void> {
  // Create a copy of the state without the image
  const stateCopy: EditorState = {
    ...state,
    spritesheet: {
      ...state.spritesheet,
      image: null,
    },
  };

  // Store the state
  try {
    localStorage.setItem(STORAGE_KEY, JSON.stringify(stateCopy));
    return;
  } catch (error) {
    console.error("Failed to save editor state:", error);
    throw new Error("Failed to save editor state. Storage might be full.");
  }
}

// Load editor state from localStorage
export async function loadEditorState(): Promise<EditorState> {
  try {
    const stateJson = localStorage.getItem(STORAGE_KEY);
    if (!stateJson) {
      return { ...defaultEditorState };
    }

    const state = JSON.parse(stateJson) as EditorState;

    // Load the spritesheet
    const spritesheetData = await loadSpritesheetFromStorage();
    if (spritesheetData) {
      state.spritesheet.image = spritesheetData.image;
      state.spritesheet.filename = spritesheetData.filename;
      state.spritesheet.width = spritesheetData.image.width;
      state.spritesheet.height = spritesheetData.image.height;
    }

    return state;
  } catch (error) {
    console.error("Failed to load editor state:", error);
    return { ...defaultEditorState };
  }
}

// Save sidebar width to localStorage
export function saveSidebarWidth(width: number): void {
  try {
    localStorage.setItem(SIDEBAR_WIDTH_KEY, width.toString());
  } catch (error) {
    console.error("Failed to save sidebar width:", error);
  }
}

// Load sidebar width from localStorage
export function loadSidebarWidth(): number | null {
  try {
    const widthStr = localStorage.getItem(SIDEBAR_WIDTH_KEY);
    if (!widthStr) return null;

    const width = parseInt(widthStr, 10);
    return isNaN(width) ? null : width;
  } catch (error) {
    console.error("Failed to load sidebar width:", error);
    return null;
  }
}

// Clear all stored data
export function clearStoredData(): void {
  localStorage.removeItem(STORAGE_KEY);
  localStorage.removeItem(SPRITESHEET_KEY);
  localStorage.removeItem(SPRITESHEET_DATA_KEY);
  localStorage.removeItem(SIDEBAR_WIDTH_KEY);
}
