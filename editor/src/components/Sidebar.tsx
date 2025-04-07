import React, { ReactElement, RefObject } from "react";
import { EditorState } from "../models";
import MapList from "./MapList";
import SpriteSelector from "./SpriteSelector";

interface SidebarProps {
  state: EditorState;
  leftPanelRef: RefObject<HTMLDivElement>;
  onResizerMouseDown: (e: React.MouseEvent) => void;
  onSpritesheetUpload: (event: React.ChangeEvent<HTMLInputElement>) => void;
  onSpriteSelected: (spriteId: number) => void;
  onNewMap: () => void;
  onMapSelected: (mapId: string) => void;
  onMapDeleted: (mapId: string) => void;
  onSave: () => void;
  onLoad: () => void;
  onExport: () => void;
  onClear: () => void;
}

function Sidebar({
  state,
  leftPanelRef,
  onResizerMouseDown,
  onSpritesheetUpload,
  onSpriteSelected,
  onNewMap,
  onMapSelected,
  onMapDeleted,
  onSave,
  onLoad,
  onExport,
  onClear,
}: SidebarProps): ReactElement {
  return (
    <div className="left-panel" ref={leftPanelRef}>
      <div className="resizer" onMouseDown={onResizerMouseDown}></div>

      <div className="panel-section">
        <h3>Spritesheet</h3>
        <input
          type="file"
          accept="image/*"
          className="file-input"
          onChange={onSpritesheetUpload}
        />
      </div>

      <div className="panel-section">
        <h3>Sprite Selection</h3>
        <SpriteSelector
          spritesheet={state.spritesheet}
          sprites={state.sprites}
          selectedSpriteId={state.selectedSpriteId}
          onSpriteSelected={onSpriteSelected}
        />
      </div>

      <div className="panel-section">
        <h3>Maps</h3>
        <button onClick={onNewMap}>New Map</button>
        <MapList
          maps={state.maps}
          selectedMapId={state.selectedMapId}
          onMapSelected={onMapSelected}
          onMapDeleted={onMapDeleted}
        />
      </div>

      <div className="panel-section">
        <h3>Actions</h3>
        <div className="button-group">
          <button onClick={onSave}>Save</button>
          <button onClick={onLoad}>Load</button>
          <button onClick={onExport}>Export</button>
          <button onClick={onClear} className="danger">
            Clear All
          </button>
        </div>
      </div>
    </div>
  );
}

export default Sidebar;
