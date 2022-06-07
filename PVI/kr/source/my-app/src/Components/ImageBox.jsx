import { Modal, Form, Button, FormGroup, Card } from "react-bootstrap";
import {React, useState} from 'react'

function ImageBox(props) {
    const [modalEditShow, setModalEditShow] = useState(false);

    function updateImage(){

    }

    function delete_image(){
        
    }

    return(
        <div style={{width:'100%', display: 'flex', justifyContent: 'center'}}>
            <Card style={{ width: '60rem', margin: '30px' }}>
                <Card.Body>
                    <Card.Title>{props.name}</Card.Title>
                    <Card.Img src={props.src} alt={props.name} />
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
                            id = "name"
                            name = "name"
                            type = "text"
                            value = {props.name}
                            />
                        </FormGroup>
                        <FormGroup>
                            <Form.Label>Edit url</Form.Label>
                            <Form.Control
                            id = "url"
                            name = "url"
                            type = "text"
                            value = {props.url}
                            />
                        </FormGroup>
                        <FormGroup>
                            <Form.Label>Edit tags</Form.Label>
                            <Form.Control
                            id = "tags"
                            name = "tags"
                            type = "text"
                            value = {props.tags}
                            />
                        </FormGroup>
                    </Form>
                </Modal.Body>
                
                <Modal.Footer>
                    <Button variant="success" onClick={() => updateImage()} style={{marginTop: 10}}> 
                        Submit
                    </Button>
                    <Button variant="danger" onClick={props.onHide} style={{marginTop: 10, marginLeft: 10}}>
                        Close
                    </Button>
                </Modal.Footer>
            </Modal>
        </div>
    )
}

export default ImageBox;