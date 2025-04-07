import React, { ReactElement } from "react";
import { EditorProvider } from "../context/EditorContext";
import MainContent from "./MainContent";
import Sidebar from "./Sidebar";

function App(): ReactElement {
  return (
    <EditorProvider>
      <div className="container">
        <Sidebar />
        <MainContent />
      </div>
    </EditorProvider>
  );
}

export default App;
