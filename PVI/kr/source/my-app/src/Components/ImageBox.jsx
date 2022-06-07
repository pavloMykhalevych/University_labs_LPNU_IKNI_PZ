import { Modal, Form, Button, FormGroup, Card, Badge } from "react-bootstrap";
import {React, useState} from 'react'
import LoadingImage from "../pages/Loading";

function ImageBox(props) {
    const [modalEditShow, setModalEditShow] = useState(false);
    var tags = props.tags.split(' ');

    function updateImage(){
        var name_upd = document.getElementById("name_upd").value;
        var url_upd = document.getElementById("url_upd").value;
        var tags_upd = document.getElementById("tags_upd").value;

        var server = 'http://kr/update_image.php';
        var formdata = new FormData();
        
        formdata.append('old_name', props.name);
        formdata.append('name', name_upd);
        formdata.append('url', url_upd);
        formdata.append('tags', tags_upd);
        formdata.append('user_id', props.user_id);

        props.setImages(Array(<LoadingImage />));
        fetch(server, {
            method : 'POST',
            header : {'Content-Type' : 'application/x-www-form-urlencoded'},
            body : formdata
        })
        .then(response => { return response.json(); })
        .then(result_data => {
            if(result_data.sever_error){
                alert(result_data.sever_error_text);
                props.showImages();
                return false;
            }
            setModalEditShow(false);
            props.showImages();
        });
    }

    function delete_image(){
        var server = 'http://kr/delete_image.php';
        var formdata = new FormData();

        formdata.append('name', props.name);
        formdata.append('user_id', props.user_id);

        props.setImages(Array(<LoadingImage />));
        fetch(server, {
            method : 'POST',
            header : {'Content-Type' : 'application/x-www-form-urlencoded'},
            body : formdata
        })
        .then(response => { return response.json(); })
        .then(result_data => {
            if(result_data.sever_error){
                alert(result_data.sever_error_text);
                props.showImages();
                return false;
            }
            props.showImages();
        });
    }

    return(
        <div style={{width:'100%', display: 'flex', justifyContent: 'center'}}>
            <Card style={{ width: '60rem', margin: '15px' }}>
                <Card.Body>
                    <Card.Title>{props.name}</Card.Title>
                    {props.src !== '' && <Card.Img style={{width: '100%',  height: '36rem', objectFit: 'contain'}} src={props.src} alt={props.name} />}
                    {tags.map(tag => <Badge pill bg="primary">{tag}</Badge>)}
                    <div style={{display: 'flex', justifyContent: 'right'}}>
                        {props.CanEdit && <Button variant="outline-secondary" onClick={() => setModalEditShow(true)} style={{marginTop: 10}}> 
                            Edit
                        </Button>}
                        {props.CanEdit && <Button variant="outline-danger" onClick={() => delete_image()} style={{marginTop: 10, marginLeft: 10}}>
                            Delete
                        </Button>}
                    </div>
                </Card.Body>
            </Card>
            <Modal
            show = {modalEditShow}
            onHide = {() => setModalEditShow(false)}
            className="text-center"
            >
                <Modal.Header closeButton>
                    <Modal.Title>
                        Edit
                    </Modal.Title>
                </Modal.Header>

                <Modal.Body>
                    <Form>
                        <FormGroup>
                            <Form.Label>Edit name</Form.Label>
                            <Form.Control
                            id = "name_upd"
                            name = "name_upd"
                            type = "text"
                            defaultValue = {props.name}
                            />
                        </FormGroup>
                        <FormGroup>
                            <Form.Label>Edit url</Form.Label>
                            <Form.Control
                            id = "url_upd"
                            name = "url_upd"
                            type = "text"
                            defaultValue = {props.src}
                            />
                        </FormGroup>
                        <FormGroup>
                            <Form.Label>Edit tags</Form.Label>
                            <Form.Control
                            id = "tags_upd"
                            name = "tags_upd"
                            type = "text"
                            defaultValue = {props.tags}
                            />
                        </FormGroup>
                    </Form>
                </Modal.Body>
                
                <Modal.Footer>
                    <Button variant="success" onClick={() => updateImage()} style={{marginTop: 10}}> 
                        Submit
                    </Button>
                    <Button variant="danger" onClick={() => setModalEditShow(false)} style={{marginTop: 10, marginLeft: 10}}>
                        Close
                    </Button>
                </Modal.Footer>
            </Modal>
        </div>
    )
}

export default ImageBox;