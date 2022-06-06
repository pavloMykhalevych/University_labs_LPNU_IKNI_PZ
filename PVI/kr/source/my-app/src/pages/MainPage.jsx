import { Image, Navbar, InputGroup, FormControl, Button, Container } from "react-bootstrap";
import LoginForm from "./Login";
import RegisterForm from "./Registration";
import React, { useState } from 'react';

function MainPage() {
    const [modalLoginShow, setModalLoginShow] = useState(false);
    const [modalRegisterShow, setModalRegisterShow] = useState(false);
    const [user_id, setUserId] = useState(0);
    const [user_name, setUserName] = useState("");

    function showImages(){

    }

    return (
        <>
            <Navbar 
            bg = "dark">
                <Container>
                    <InputGroup>
                        <FormControl onChange={()=>showImages()}
                        placeholder="Enter image tag"
                        />
                        {user_name === '' && <Button variant="outline-secondary" onClick={() => setModalLoginShow(true)}>Log in</Button>}
                        {user_name === '' && <Button variant="outline-secondary" onClick={() => setModalRegisterShow(true)}>Sign in</Button>}
                        {user_name !== '' && <Button variant="outline-secondary" onClick={() => {setUserId(0); setUserName('');}}>Sign out</Button>}
                    </InputGroup>
                </Container>
                <span style={{color: 'white', fontFamily: 'Lucida Console', marginRight: 20}}>{user_name}</span>
                <Image
                        style={{
                        width: 60,
                        height: 60,
                        }}
                        src="https://www.svgrepo.com/show/327465/person-circle.svg"
                        roundedCircle
                    />
            </Navbar>
            <LoginForm 
                show={modalLoginShow}
                onHide={() => setModalLoginShow(false)}
                setUserId = {setUserId}
                setUserName = {setUserName}
            />
            <RegisterForm 
                show={modalRegisterShow}
                onHide={() => setModalRegisterShow(false)}
                setUserId = {setUserId}
                setUserName = {setUserName}
            />
        </>
    )
}

export default MainPage;