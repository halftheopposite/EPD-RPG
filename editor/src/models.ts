// Data models for the tilemap editor

export interface Point {
  x: number;
  y: number;
}

export interface Size {
  width: number;
  height: number;
}

export interface Sprite {
  id: number;
  x: number;
  y: number;
  width: number;
  height: number;
  imageData?: ImageData;
}

export interface TileMap {
  id: string;
  name: string;
  width: number;
  height: number;
  tiles: number[][]; // 2D array of sprite IDs
}

export interface EditorState {
  spritesheet: {
    image: HTMLImageElement | null;
    filename: string;
    width: number;
    height: number;
  };
  sprites: Sprite[];
  maps: TileMap[];
  selectedSpriteId: number | null;
  selectedMapId: string | null;
  hoverPosition: Point | null;
}

// Default state for the editor
export const defaultEditorState: EditorState = {
  spritesheet: {
    image: null,
    filename: "",
    width: 0,
    height: 0,
  },
  sprites: [],
  maps: [],
  selectedSpriteId: null,
  selectedMapId: null,
  hoverPosition: null,
};

// Constants
export const TILE_SIZE = 16; // 16x16 pixels per tile
export const MAP_WIDTH = 12; // 12 tiles wide
export const MAP_HEIGHT = 12; // 12 tiles high
export const DISPLAY_SCALE = 2; // Scale factor for display
