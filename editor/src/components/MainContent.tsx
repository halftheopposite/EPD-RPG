import { ReactElement } from "react";
import { EditorState, TileMap } from "../models";
import MapCanvas from "./MapCanvas";

interface MainContentProps {
  state: EditorState;
  selectedMap?: TileMap;
  onTilePlaced: (x: number, y: number) => void;
  onTileRemoved: (x: number, y: number) => void;
  onHover: (x: number, y: number) => void;
  onMouseLeave: () => void;
}

function MainContent({
  state,
  selectedMap,
  onTilePlaced,
  onTileRemoved,
  onHover,
  onMouseLeave,
}: MainContentProps): ReactElement {
  return (
    <div className="right-panel">
      <h2>{selectedMap ? selectedMap.name : "No Map Selected"}</h2>

      {selectedMap ? (
        <div className="map-canvas-container">
          <MapCanvas
            map={selectedMap}
            spritesheet={state.spritesheet}
            sprites={state.sprites}
            selectedSpriteId={state.selectedSpriteId}
            hoverPosition={state.hoverPosition}
            onTilePlaced={onTilePlaced}
            onTileRemoved={onTileRemoved}
            onHover={onHover}
            onMouseLeave={onMouseLeave}
          />
        </div>
      ) : (
        <div className="no-map-message">
          <p>
            Please select a map from the sidebar or create a new one to start
            editing.
          </p>
        </div>
      )}
    </div>
  );
}

export default MainContent;
