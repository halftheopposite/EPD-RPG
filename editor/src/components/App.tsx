import React, { ReactElement, useEffect, useRef, useState } from "react";
import {
  downloadFile,
  generateMapsHeader,
  generateSpritesHeader,
} from "../exporter";
import {
  defaultEditorState,
  EditorState,
  MAP_HEIGHT,
  MAP_WIDTH,
  TILE_SIZE,
  TileMap,
} from "../models";
import {
  clearStoredData,
  loadEditorState,
  loadSidebarWidth,
  saveEditorState,
  saveSidebarWidth,
  saveSpritesheetToStorage,
} from "../storage";
import MainContent from "./MainContent";
import Sidebar from "./Sidebar";

// Sidebar width configuration
const SIDEBAR_CONFIG = {
  DEFAULT_WIDTH: 300,
  MIN_WIDTH: 200,
  MAX_WIDTH: 700,
};

function App(): ReactElement {
  const [state, setState] = useState<EditorState>({ ...defaultEditorState });
  const [resizing, setResizing] = useState(false);
  const [sidebarWidth, setSidebarWidth] = useState(
    SIDEBAR_CONFIG.DEFAULT_WIDTH
  );
  const leftPanelRef = useRef<HTMLDivElement>(null);
  const startXRef = useRef(0);
  const startWidthRef = useRef(0);

  // Load editor state and sidebar width on mount
  useEffect(() => {
    const loadState = async () => {
      try {
        // Load editor state
        const loadedState = await loadEditorState();
        setState(loadedState);
        console.log("Editor state loaded from local storage");

        // Load sidebar width
        const savedWidth = loadSidebarWidth();
        if (savedWidth) {
          // Ensure the width is within constraints
          const constrainedWidth = Math.max(
            SIDEBAR_CONFIG.MIN_WIDTH,
            Math.min(SIDEBAR_CONFIG.MAX_WIDTH, savedWidth)
          );
          setSidebarWidth(constrainedWidth);
        }
      } catch (error) {
        console.error("Failed to load editor state:", error);
      }
    };

    loadState();
  }, []);

  // Apply sidebar width to the DOM element whenever it changes
  useEffect(() => {
    if (leftPanelRef.current) {
      leftPanelRef.current.style.width = `${sidebarWidth}px`;
    }
  }, [sidebarWidth]);

  // Handle resizing
  useEffect(() => {
    if (!resizing) return;

    function handleMouseMove(e: MouseEvent) {
      const width = startWidthRef.current + (e.clientX - startXRef.current);

      // Apply min and max constraints
      const constrainedWidth = Math.max(
        SIDEBAR_CONFIG.MIN_WIDTH,
        Math.min(SIDEBAR_CONFIG.MAX_WIDTH, width)
      );

      setSidebarWidth(constrainedWidth);
    }

    function handleMouseUp() {
      setResizing(false);

      // Save the sidebar width when resizing is done
      saveSidebarWidth(sidebarWidth);
    }

    document.addEventListener("mousemove", handleMouseMove);
    document.addEventListener("mouseup", handleMouseUp);

    return () => {
      document.removeEventListener("mousemove", handleMouseMove);
      document.removeEventListener("mouseup", handleMouseUp);
    };
  }, [resizing, sidebarWidth]);

  function handleResizerMouseDown(e: React.MouseEvent) {
    e.preventDefault(); // Prevent text selection during resize
    setResizing(true);
    startXRef.current = e.clientX;
    startWidthRef.current = sidebarWidth;
  }

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

  // Find the selected map
  const selectedMap = state.selectedMapId
    ? state.maps.find((map) => map.id === state.selectedMapId)
    : undefined;

  return (
    <div className="container">
      <Sidebar
        state={state}
        leftPanelRef={leftPanelRef}
        onResizerMouseDown={handleResizerMouseDown}
        onSpritesheetUpload={handleSpritesheetUpload}
        onSpriteSelected={handleSpriteSelected}
        onNewMap={handleNewMap}
        onMapSelected={handleMapSelected}
        onMapDeleted={handleMapDeleted}
        onSave={handleSave}
        onLoad={handleLoad}
        onExport={handleExport}
        onClear={handleClear}
      />

      <MainContent
        state={state}
        selectedMap={selectedMap}
        onTilePlaced={handleTilePlaced}
        onTileRemoved={handleTileRemoved}
        onHover={handleHover}
        onMouseLeave={handleMouseLeave}
      />
    </div>
  );
}

export default App;
