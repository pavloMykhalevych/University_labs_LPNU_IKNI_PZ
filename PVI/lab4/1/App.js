import React  from "react";
import ChessField from "./componets/ChessField";
import MyForm from "./componets/MyForm";
import "./App.css"
import SomeComponent from "./componets/SomeComponent";
import 'bootstrap/dist/css/bootstrap.min.css';


const mystyle = {
  margin: "auto",
  width: "100%"
};

function App() {
  return (
    <div className="App" style={mystyle}>
      <ChessField/>
      <MyForm/>
      <SomeComponent/>
    </div>
  );
}

export default App;
