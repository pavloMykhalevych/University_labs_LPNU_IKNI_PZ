import "./App.css";
import Table from "./Components/Table";
import Links from "./Components/Links";
import MyForm from './Components/MyForm';
import RandomImage from "./Components/RandomImage"
import Player from "./Components/Player";
import "bootstrap/dist/css/bootstrap.min.css";

function App() {
  return (
    <div className="App">
      <MyForm />
      <Player />
      <Table />
      <Links />
      <RandomImage />
    </div>
  );
}

export default App;
