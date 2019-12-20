import React from "react";
// @material-ui/core components
import { makeStyles } from "@material-ui/core/styles";
// core components
import GridItem from "components/Grid/GridItem.js";
import GridContainer from "components/Grid/GridContainer.js";
import Table from "components/Table/Table.js";
import Card from "components/Card/Card.js";
import CardHeader from "components/Card/CardHeader.js";
import CardBody from "components/Card/CardBody.js";
import Ranking_serv from "./Ranking_service";
import axios from "axios";

const styles = {
  cardCategoryWhite: {
    "&,& a,& a:hover,& a:focus": {
      color: "rgba(255,255,255,.62)",
      margin: "0",
      fontSize: "14px",
      marginTop: "0",
      marginBottom: "0"
    },
    "& a,& a:hover,& a:focus": {
      color: "#FFFFFF"
    }
  },
  cardTitleWhite: {
    color: "#FFFFFF",
    marginTop: "0px",
    minHeight: "auto",
    fontWeight: "300",
    fontFamily: "'Roboto', 'Helvetica', 'Arial', sans-serif",
    marginBottom: "3px",
    textDecoration: "none",
    "& small": {
      color: "#777",
      fontSize: "65%",
      fontWeight: "400",
      lineHeight: "1"
    }
  }
};

const useStyles = makeStyles(styles);


// let jugadores = [];

const jugadores = [
  // Devuelve todos los jugadores de la misma empresa

  {
    urlImage: "url de la imagen que se genero por defecto",
    id: "1",
    nombre: "Ash Ketchum",
    puntaje: "2225"
  },
  {
    urlImage: "url de la imagen que se genero por defecto",
    id: "2",
    nombre: "Luis Ramos",
    puntaje: "1950"
  },
  {
    urlImage: "url de la imagen que se genero por defecto",
    id: "3",
    nombre: "Carlos Ezpinoza",
    puntaje: "920"
  },
  {
    urlImage: "url de la imagen que se genero por defecto",
    id: "4",
    nombre: "Konrad Trejo",
    puntaje: "850"
  },

  {
    urlImage: "url de la imagen que se genero por defecto",
    id: "5",
    nombre: "Alex Avila",
    puntaje: "0"
  }
];




export default function TableList() {



const RANKING_JSON ="http://ec2-18-219-251-98.us-east-2.compute.amazonaws.com/getRanking";
const Empresa = "eres";
function players ( url ) {
    console.log("esperando pos");

      axios.post(url,Empresa)
        .then(result => {
         console.log("hola ", ((result.data).data).jugador)
         return ((result.data).data).jugador ;

        }).catch(console.log)

      
      console.log("pos obtenida")
      
  }
  console.log("funcion",players())

  //const listItems = players(RANKING_JSON).map(jugador => [
  //jugador.id,
  //jugador.nombre,
  //jugador.puntaje
  //]);

const listItems = jugadores.map(jugador => [
  jugador.id,
  jugador.nombre,
  jugador.puntaje
  ]);

  const classes = useStyles();
  return (
    <GridContainer>
      <GridItem xs={12} sm={12} md={12}>
        <Card plain>
          <CardHeader plain color="primary">
            <h4 className={classes.cardTitleWhite}>
              Participantes de la Universidad Nacional de Ingeniera
            </h4>
            <p className={classes.cardCategoryWhite}></p>
          </CardHeader>
          <CardBody>
            <Table
              tableHeaderColor="primary"
              tableHead={["Puesto", "Nombre", "Puntaje"]}
              tableData={listItems}
            />
          </CardBody>
        </Card>
      </GridItem>
    </GridContainer>
  );
}
