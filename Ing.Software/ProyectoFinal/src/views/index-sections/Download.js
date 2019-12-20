import React from "react";

// reactstrap components
import { Button, Container, Row, Col, UncontrolledTooltip } from "reactstrap";

// core components

function Download() {
  return (
    <>
      <div
        className="section section-download"
        data-background-color="black"
        id="download-section"
      >
        <Container>
          <Row className="justify-content-md-center">
            <Col className="text-center" lg="8" md="12">
              <h3 className="title">¿Quieres tener pokeunis en tu empresa ?</h3>
              <h5 className="description">
                Nosotros llevamos pokeunis a tu empresa para que todos 
                puedan divertirse capturando pokeunis.
                Tan solo respondiendo preguntas sencilas o haciendo pequeños retos.
                Si estas interesado mandanos un correo a pokeuni@uni.pe o llamanos al 911456278.
              </h5>
            </Col>
            <Col className="text-center" lg="8" md="12">
              <Button
                className="btn-round mr-1"
                color="info"
                href="https://play.google.com/store"
                role="button"
                size="lg"
              >
                Download App Mobile
              </Button>
              
            </Col>
          </Row>
          <br></br>
          <br></br>

          <br></br>
          <Row className="justify-content-md-center sharing-area text-center">
            <Col className="text-center" lg="8" md="12">
              <h3>No te pierdas esta gran diversión !!</h3>
            </Col>
            
          </Row>
        </Container>
      </div>
    </>
  );
}

export default Download;
