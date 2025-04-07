import { ReactElement } from "react";
import { TileMap } from "../models";

interface MapListProps {
  maps: TileMap[];
  selectedMapId: string | null;
  onMapSelected: (mapId: string) => void;
  onMapDeleted: (mapId: string) => void;
}

function MapList({
  maps,
  selectedMapId,
  onMapSelected,
  onMapDeleted,
}: MapListProps): ReactElement {
  if (maps.length === 0) {
    return <p>No maps created</p>;
  }

  return (
    <div className="map-list">
      {maps.map((map) => (
        <div
          key={map.id}
          className={`map-item ${selectedMapId === map.id ? "selected" : ""}`}
          onClick={() => onMapSelected(map.id)}
        >
          <span>{map.name}</span>
          <div className="map-actions">
            <button
              className="danger"
              onClick={(e) => {
                e.stopPropagation();
                if (
                  window.confirm(
                    `Are you sure you want to delete the map "${map.name}"?`
                  )
                ) {
                  onMapDeleted(map.id);
                }
              }}
            >
              Delete
            </button>
          </div>
        </div>
      ))}
    </div>
  );
}

export default MapList;
