import { Image, Navbar, InputGroup, FormControl, Button, Container } from "react-bootstrap";
import LoginForm from "./Login";
import RegisterForm from "./Registration";
import React, { useState, useEffect } from 'react';
import ImageBox from "../Components/ImageBox";
import LoadingImage from "./Loading";
import NoImage from "./NoImages";
import UploadImageForm from "../Components/UploadImageForm";

function MainPage() {
    const [modalLoginShow, setModalLoginShow] = useState(false);
    const [modalRegisterShow, setModalRegisterShow] = useState(false);
    const [modalUploadShow, setModalUploadShow] = useState(false);
    const [user_id, setUserId] = useState(0);
    const [user_name, setUserName] = useState("");
    const [images, setImages] = useState(Array(<NoImage />));

    function showImages(tags, user_id){
        var server = 'http://kr/get_images.php';
        var formdata = new FormData();
        formdata.append('tags', tags);
        setImages(Array(<LoadingImage />));
        fetch(server, {
            method : 'POST',
            header : {'Content-Type' : 'application/x-www-form-urlencoded'},
            body : formdata
        })
        .then(response => { return response.json(); })
        .then(result_data => {
            if(result_data.sever_error){
                alert(result_data.sever_error_text);
                return false;
            }
            if(result_data.data.length > 0){
                var new_images = Array();
                result_data.data.map(image => {
                    new_images.push(
                    <ImageBox 
                        user_id={user_id} 
                        name={image.name} 
                        src={image.url} 
                        CanEdit={((image.user_id === user_id) || (user_id === '1'))} 
                        tags={image.tags}
                        showImages = {()=>showImages(document.getElementById('input_tag').value, user_id)}
                        setImages = {setImages}
                    />)})
                setImages(new_images);
            }else{
                setImages(Array(<NoImage />));
            }
        });
    }
    
    function setId(id){
        setUserId(id);
        showImages(document.getElementById('input_tag').value, id);
    }

    useEffect(() => {
        showImages(document.getElementById('input_tag').value, user_id);
    }, []);

    return (
        <>
            <Navbar sticky='top' onChange={(e)=>showImages(e.target.value, user_id)}
            bg = "dark">
                <Container>
                    <InputGroup>
                        <FormControl style={{marginRight:'20px', borderRadius: '10px'}}
                        placeholder="Enter image tag"
                        id = 'input_tag'
                        />
                        {user_name === '' && 
                        <Button variant="outline-secondary" onClick={() => setModalLoginShow(true)} style={{borderTopLeftRadius: '10px', borderBottomLeftRadius: '10px'}}>
                            Sign in
                        </Button>}
                        {user_name === '' && 
                        <Button variant="outline-secondary" onClick={() => setModalRegisterShow(true)} style={{borderTopRightRadius: '10px', borderBottomRightRadius: '10px'}}>
                            Sign up
                        </Button>}
                        {user_name !== '' && 
                        <Button 
                        variant="outline-secondary" 
                        onClick={() => {setId(0); setUserName('');}} 
                        style={{borderTopLeftRadius: '10px', borderBottomLeftRadius: '10px'}}>Sign out</Button>}
                        {user_name !== '' && 
                        <Button 
                        variant="outline-secondary" 
                        onClick={() => {setModalUploadShow(true);}} 
                        style={{borderTopRightRadius: '10px', borderBottomRightRadius: '10px'}}>Upload image</Button>}
                    </InputGroup>
                </Container>
                {user_name !== '' && <span style={{color: 'white', fontFamily: 'Lucida Console', marginRight: 20}}>{user_name}</span>}
                {user_name !== '' && <Image
                        style={{
                        width: 60,
                        height: 60,
                        }}
                        src="https://www.svgrepo.com/show/327465/person-circle.svg"
                        roundedCircle
                    />}
            </Navbar>
            <LoginForm 
                show={modalLoginShow}
                onHide={() => {setModalLoginShow(false)}}
                setUserId = {setId}
                setUserName = {setUserName}
            />
            <RegisterForm 
                show={modalRegisterShow}
                onHide={() => {setModalRegisterShow(false)}}
                setUserId = {setId}
                setUserName = {setUserName}
            />
            <UploadImageForm 
                show={modalUploadShow}
                onHide={()=>{setModalUploadShow(false)}}
                user_id = {user_id}
                setImages = {setImages}
                showImages = {()=>showImages(document.getElementById('input_tag').value, user_id)}
            />
            {images}
        </>
    )
}

export default MainPage;