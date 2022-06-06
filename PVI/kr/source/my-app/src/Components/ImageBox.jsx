import { Image } from "react-bootstrap";

function ImageBox(props) {
    const [modalShow, setModalShow] = useState(false);
    function resize(CanEdit){

    }

    return(
        <>
            <Image {...props} onClick={() => setModalShow(true)} />
            <Modal
            show = {modalShow}
            onHide = {() => setModalShow(false)}
            size = "lg"
            id="LogInForm"
            aria-labelledby="contained-modal-title-vcenter"
            centered
            className="text-center"
            >
                <Modal.Header closeButton>
                    <Modal.Title>
                        {props.name}
                    </Modal.Title>
                </Modal.Header>

                <Modal.Body>
                resize(props.CanEdit, props.src)
                </Modal.Body>
                
                <Modal.Footer>
                    {props.CanEdit && <Button variant="outline-secondary" onClick={() => validate()} style={{marginTop: 10}}> 
                        Edit
                    </Button>}
                    {props.CanEdit && <Button variant="outline-secondary" onClick={props.onHide} style={{marginTop: 10, marginLeft: 10}}>
                        Delete
                    </Button>}
                </Modal.Footer>
            </Modal>
        </>
    )
}

export default ImageBox;