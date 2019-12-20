/* eslint react/no-multi-comp: 0, react/prop-types: 0 */

import React, { useState } from "react";
import { Button, Modal, ModalHeader, ModalBody, ModalFooter } from "reactstrap";
import { withRouter } from "react-router-dom";
import Timer from "../timer/Timer"

const ModalExample = props => {
  const {
    buttonLabel = "Enviar",
    className = "goooo",
    resultado = props.resultado,

  } = props;

  const [modal, setModal] = useState(false);
  const toggle = () => setModal(!modal);

  const [disabled, setDisabled] = useState(false);
  const [cabecera, setCabecera] = useState("aaaaaas");
  const [cuerpo, setCuerpo] = useState("ssssss");
  
  const cabCorr = () => setCabecera("Felicitaciones");
  const cabInco = () => setCabecera("Vuelve a intentarlo");

  function setCue(text){
    setCuerpo(text)
  }

  function showModal() {
    if (resultado === "incorrecto") {
      return (
        <Modal isOpen={modal} className={className}>
          <ModalHeader >Vuelve a intentarlo</ModalHeader>
          <ModalBody>
            La respuesta no es la correcta, espere mientras se recupera
            {showTimer()} 
          </ModalBody>
          <ModalFooter>
            <Button href="./game/perfil" color="primary" onClick={toggle}>
              Ir a perfil
          </Button>{" "}
            <Button href="./maps" color="secondary" onClick={toggle} disabled={disabled}>
              Seguir
          </Button>
          </ModalFooter>
        </Modal>
      )  
    } else if (resultado === "correcto") {
      return (
        <Modal isOpen={modal}  className={className} >
          <ModalHeader  >Felicitaciones</ModalHeader>
          <ModalBody>
          Pokemon capturado, puede revisar su perfil.
          </ModalBody>
          <ModalFooter>
            <Button href="./game/perfil" color="primary" onClick={toggle}>
              Ir a perfil
          </Button>{" "}
            <Button href="./maps" color="secondary" onClick={toggle} disabled={disabled}>
              Seguir
          </Button>
          </ModalFooter>
        </Modal>
      )
    }
    
    
  }
  function showTimer() {
    return(
      <Timer disabled={disabled} setDisabled={setDisabled} />
    )
  }

  // function validar() {

  //   console.log("resultado: ", resultado)
  //   var cabecera = ""
  //   var cuerpo = ""
  //   if (resultado === "correcto") {
  //     setCab("Felicitaciones")
  //     console.log(cabecera)
  //     cuerpo = "Pokemon capturado, puede revisar su perfil."
  //   } else {
  //     setCab("Vuelve a intentarlo")
  //     cuerpo = "La respuesta no es la correcta, espere mientras se recupera"
  //   }

  //   //   const { history } = props;
  //   //   const { from } = { from: { pathname: "/index" } };
  //   //     history.push(from);
  // }

  return (
    // validar(),
    <div>
    {console.log("aaaaaa", resultado)}
    <Button type={props.type} color="primary" onClick={toggle}>
      {buttonLabel}
    </Button>
    {showModal()}
    </div>
  );
};

export default ModalExample;
