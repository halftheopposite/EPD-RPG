import React, {
  createContext,
  ReactElement,
  useContext,
  useEffect,
  useState,
} from "react";
import {
  downloadFile,
  generateMapsHeader,
  generateSpritesHeader,
} from "../exporter";
import { defaultEditorState, EditorState, TileMap } from "../models";
import {
  clearStoredData,
  loadEditorState,
  saveEditorState,
  saveSpritesheetToStorage,
} from "../storage";

// Constants for map and tile dimensions
const MAP_WIDTH = 12;
const MAP_HEIGHT = 12;
const TILE_SIZE = 16;

interface EditorContextType {
  state: EditorState;
  selectedMap?: TileMap;
  handleSpritesheetUpload: (
    event: React.ChangeEvent<HTMLInputElement>
  ) => Promise<void>;
  handleSpriteSelected: (spriteId: number) => void;
  handleNewMap: () => void;
  handleMapSelected: (mapId: string) => void;
  handleMapDeleted: (mapId: string) => void;
  handleMapRenamed: (mapId: string, newName: string) => void;
  handleTilePlaced: (x: number, y: number) => void;
  handleTileRemoved: (x: number, y: number) => void;
  handleHover: (x: number, y: number) => void;
  handleMouseLeave: () => void;
  handleSave: () => Promise<void>;
  handleLoad: () => Promise<void>;
  handleExport: () => void;
  handleClear: () => void;
}

const EditorContext = createContext<EditorContextType | undefined>(undefined);

export function EditorProvider({
  children,
}: {
  children: React.ReactNode;
}): ReactElement {
  const [state, setState] = useState<EditorState>({ ...defaultEditorState });

  // Load editor state on mount
  useEffect(() => {
    const loadState = async () => {
      try {
        // Load editor state
        const loadedState = await loadEditorState();
        setState(loadedState);
        console.log("Editor state loaded from local storage");
      } catch (error) {
        console.error("Failed to load editor state:", error);
      }
    };

    loadState();
  }, []);

  // Find the selected map
  const selectedMap = state.selectedMapId
    ? state.maps.find((map) => map.id === state.selectedMapId)
    : undefined;

  async function handleSpritesheetUpload(
    event: React.ChangeEvent<HTMLInputElement>
  ) {
    const file = event.target.files?.[0];
    if (!file) return;

    try {
      // Save the spritesheet to storage
      const dataUrl = await saveSpritesheetToStorage(file);

      // Load the image
      const image = new Image();
      image.src = dataUrl;

      // Wait for the image to load
      await new Promise<void>((resolve, reject) => {
        image.onload = () => resolve();
        image.onerror = () =>
          reject(new Error("Failed to load spritesheet image"));
      });

      // Update the state
      setState((prevState) => {
        // Generate sprites from the spritesheet
        const sprites = [];
        let id = 1; // Start from 1, 0 is reserved for empty tiles

        // Calculate number of sprites in the spritesheet
        const spritesWide = Math.floor(image.width / TILE_SIZE);
        const spritesHigh = Math.floor(image.height / TILE_SIZE);

        // Generate sprites
        for (let y = 0; y < spritesHigh; y++) {
          for (let x = 0; x < spritesWide; x++) {
            sprites.push({
              id,
              x: x * TILE_SIZE,
              y: y * TILE_SIZE,
              width: TILE_SIZE,
              height: TILE_SIZE,
            });
            id++;
          }
        }

        return {
          ...prevState,
          spritesheet: {
            image,
            filename: file.name,
            width: image.width,
            height: image.height,
          },
          sprites,
        };
      });

      console.log("Spritesheet loaded and saved successfully");
    } catch (error) {
      console.error("Failed to load spritesheet:", error);
    }
  }

  function handleSpriteSelected(spriteId: number) {
    setState((prevState) => ({
      ...prevState,
      selectedSpriteId: spriteId,
    }));
  }

  function handleNewMap() {
    const mapName = prompt("Enter a name for the new map:");
    if (!mapName) return;

    // Create a new map
    const newMap: TileMap = {
      id: Date.now().toString(),
      name: mapName,
      width: MAP_WIDTH,
      height: MAP_HEIGHT,
      tiles: Array(MAP_HEIGHT)
        .fill(0)
        .map(() => Array(MAP_WIDTH).fill(0)),
    };

    // Add the map to the state and select it
    setState((prevState) => ({
      ...prevState,
      maps: [...prevState.maps, newMap],
      selectedMapId: newMap.id,
    }));

    console.log(`Map "${mapName}" created`);
  }

  function handleMapSelected(mapId: string) {
    setState((prevState) => ({
      ...prevState,
      selectedMapId: mapId,
    }));
  }

  function handleMapDeleted(mapId: string) {
    setState((prevState) => {
      // If the deleted map was selected, deselect it
      const newSelectedMapId =
        prevState.selectedMapId === mapId ? null : prevState.selectedMapId;

      return {
        ...prevState,
        maps: prevState.maps.filter((map) => map.id !== mapId),
        selectedMapId: newSelectedMapId,
      };
    });

    console.log("Map deleted");
  }

  function handleMapRenamed(mapId: string, newName: string) {
    if (!newName.trim()) {
      console.error("Map name cannot be empty");
      return;
    }

    setState((prevState) => {
      const mapIndex = prevState.maps.findIndex((map) => map.id === mapId);
      if (mapIndex === -1) return prevState;

      // Create a deep copy of the maps array
      const newMaps = [...prevState.maps];

      // Update the map name
      newMaps[mapIndex] = {
        ...newMaps[mapIndex],
        name: newName.trim(),
      };

      return {
        ...prevState,
        maps: newMaps,
      };
    });

    console.log(`Map renamed to "${newName}"`);
  }

  function handleTilePlaced(x: number, y: number) {
    if (!state.selectedMapId || !state.selectedSpriteId) return;

    setState((prevState) => {
      const mapIndex = prevState.maps.findIndex(
        (map) => map.id === prevState.selectedMapId
      );
      if (mapIndex === -1) return prevState;

      // Create a deep copy of the maps array and the selected map's tiles
      const newMaps = [...prevState.maps];
      const newTiles = newMaps[mapIndex].tiles.map((row) => [...row]);

      // Update the tile
      newTiles[y][x] = prevState.selectedSpriteId!;
      newMaps[mapIndex] = {
        ...newMaps[mapIndex],
        tiles: newTiles,
      };

      return {
        ...prevState,
        maps: newMaps,
      };
    });
  }

  function handleTileRemoved(x: number, y: number) {
    if (!state.selectedMapId) return;

    setState((prevState) => {
      const mapIndex = prevState.maps.findIndex(
        (map) => map.id === prevState.selectedMapId
      );
      if (mapIndex === -1) return prevState;

      // Create a deep copy of the maps array and the selected map's tiles
      const newMaps = [...prevState.maps];
      const newTiles = newMaps[mapIndex].tiles.map((row) => [...row]);

      // Remove the tile (set to 0, which represents an empty tile)
      newTiles[y][x] = 0;
      newMaps[mapIndex] = {
        ...newMaps[mapIndex],
        tiles: newTiles,
      };

      return {
        ...prevState,
        maps: newMaps,
      };
    });
  }

  function handleHover(x: number, y: number) {
    setState((prevState) => ({
      ...prevState,
      hoverPosition: { x, y },
    }));
  }

  function handleMouseLeave() {
    setState((prevState) => ({
      ...prevState,
      hoverPosition: null,
    }));
  }

  async function handleSave() {
    try {
      await saveEditorState(state);
      console.log("Editor state saved to local storage");
    } catch (error) {
      console.error("Failed to save editor state:", error);
    }
  }

  async function handleLoad() {
    try {
      const loadedState = await loadEditorState();
      setState(loadedState);
      console.log("Editor state loaded from local storage");
    } catch (error) {
      console.error("Failed to load editor state:", error);
    }
  }

  function handleExport() {
    if (state.maps.length === 0) {
      console.log("No maps to export");
      return;
    }

    // Generate header files
    const mapsHeader = generateMapsHeader(state);
    const spritesHeader = generateSpritesHeader(state);

    // Download the files
    downloadFile("maps.h", mapsHeader);
    downloadFile("sprites.h", spritesHeader);

    console.log("Header files exported successfully");
  }

  function handleClear() {
    if (
      window.confirm(
        "Are you sure you want to clear all data? This action cannot be undone."
      )
    ) {
      // Clear the state
      setState({ ...defaultEditorState });

      // Clear stored data
      clearStoredData();

      console.log("All data cleared");
    }
  }

  const value = {
    state,
    selectedMap,
    handleSpritesheetUpload,
    handleSpriteSelected,
    handleNewMap,
    handleMapSelected,
    handleMapDeleted,
    handleMapRenamed,
    handleTilePlaced,
    handleTileRemoved,
    handleHover,
    handleMouseLeave,
    handleSave,
    handleLoad,
    handleExport,
    handleClear,
  };

  return (
    <EditorContext.Provider value={value}>{children}</EditorContext.Provider>
  );
}

export function useEditor(): EditorContextType {
  const context = useContext(EditorContext);
  if (context === undefined) {
    throw new Error("useEditor must be used within an EditorProvider");
  }
  return context;
}
