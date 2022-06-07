import { Modal, Form, Button, FormGroup } from "react-bootstrap";
import LoadingImage from "../pages/Loading";

function UploadImageForm(props) {
    function sendImage(){
        var name_insert = document.getElementById("name_insert").value;
        var url_insert = document.getElementById("url_insert").value;
        var tags_insert = document.getElementById("tags_insert").value;

        var server = 'http://kr/insert_image.php';
        var formdata = new FormData();
        formdata.append('name', name_insert);
        formdata.append('url', url_insert);
        formdata.append('tags', tags_insert);
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
                return false;
            }
            props.onHide();
            props.showImages();
        });
    }

    return(
        <>
            <Modal
            {...props}
            className="text-center"
            >
                <Modal.Header closeButton>
                    <Modal.Title>
                        Upload
                    </Modal.Title>
                </Modal.Header>

                <Modal.Body>
                    <Form>
                        <FormGroup>
                            <Form.Label>Set name</Form.Label>
                            <Form.Control
                            id = "name_insert"
                            name = "name_insert"
                            type = "text"
                            />
                        </FormGroup>
                        <FormGroup>
                            <Form.Label>Set url</Form.Label>
                            <Form.Control
                            id = "url_insert"
                            name = "url_insert"
                            type = "text"
                            />
                        </FormGroup>
                        <FormGroup>
                            <Form.Label>Set tags</Form.Label>
                            <Form.Control
                            id = "tags_insert"
                            name = "tags_insert"
                            type = "text"
                            />
                        </FormGroup>
                    </Form>
                </Modal.Body>
                
                <Modal.Footer>
                    <Button variant="success" onClick={() => sendImage()} style={{marginTop: 10}}> 
                        Submit
                    </Button>
                    <Button variant="danger" onClick={props.onHide} style={{marginTop: 10, marginLeft: 10}}>
                        Close
                    </Button>
                </Modal.Footer>
            </Modal>
        </>
    )
}

export default UploadImageForm;