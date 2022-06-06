import "./App.css";
import "bootstrap/dist/css/bootstrap.min.css";
import MainPage from "./pages/MainPage";
import { Routes, Route } from 'react-router-dom'
import LoginForm from './pages/Login';
import RegisterForm from "./pages/Registration";

function App() {
  return (
    <>
      <MainPage />
      <Routes>
          <Route path = "/registration" element = {RegisterForm}/>
          <Route path = "/login" element = {LoginForm}/>
      </Routes>
    </>
  );
}

export default App;
