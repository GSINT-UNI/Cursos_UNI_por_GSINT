import React, { Component } from "react";
import { render } from "react-dom";
import L from "leaflet";
import { Map, Marker, Popup, TileLayer } from "react-leaflet";
import "bootstrap/dist/css/bootstrap.min.css";
import axios from "axios";
import ModalExample from "./ModalExample"

//link del back
// const linkForAnswer = `https://jsonplaceholder.typicode.com/users`;
const linkForAnswer = `https://api.myjson.com/bins/enlbk`;
// const linkForAnswer = `https://my-json-server.typicode.com/typicode/demo/posts`;
// const linkForAnswer = `https://my-json-server.typicode.com/LuisERG/demo/posts/1`;
export const pointerIcon = new L.Icon({
  iconUrl: require("../iconos/voulvas.jpg"),
  iconAnchor: [12.5, 25],
  popupAnchor: [0, -25],
  iconSize: [25, 25],
});

const abc = {
  respuestas: ["opción a", "opción b", "opción c"]
};

//pokemonIcon define los iconos que van a ir en los marcadores
//en mapa apartir del nombre del pokemon
function pokemonIcon(name) {
  return new L.Icon({
    iconUrl: require("../iconos/" + name + ".jpg"),
    iconAnchor: [12.5, 25],
    popupAnchor: [0, -25],
    iconSize: [25, 25]
  });
}

class Mapa extends Component {
  state = {
    lat: 51.505,
    lng: -0.09,
    zoom: 18,
    selectedOption: "default",
    resultado: "none",
    show: false,
    token: "random",
    id: "iduser"
  };

  showMarkers(pokeInfo){
    if (pokeInfo.state === "free") {
      return (
        <Marker
          position={[pokeInfo.position.x, pokeInfo.position.y]}
          icon={pokemonIcon(pokeInfo.name)}
        >
          <Popup>
            <form onSubmit={this.handleFormSubmit}>
              <div className="form-group">
                <label>{pokeInfo.question}</label>
              </div>
              {/* cambiar cuando el backend levante servicio
              {this.showOptions(pokeInfo.options, this.state.selectedOption) }  */}
              {this.showOptions(abc.respuestas, this.state.selectedOption)}
              <div className="form-group">
                {/* <button type="submit" className="btn btn-primary btn-sm">
                  Enviar
                </button> */}
                <ModalExample type={"submit"} resultado={this.state.resultado}/>
                {/* <ModalExample type={"submit"} resultado="incorrecto"/> */}
              </div>
            </form>
          </Popup>
        </Marker>
      )
    }
  }

  showPokemons(){
    const pokeData = this.props.pokeData;
    if (pokeData[0]) {
      console.log("pokedata defined");
      return pokeData.map(pokeInfo => (
        this.showMarkers(pokeInfo)
      ))
    }
  }

  handleOptionChange = changeEvent => {
    this.setState({
      selectedOption: changeEvent.target.value
    });
  };

  handleFormSubmit = formSubmitEvent => {
    formSubmitEvent.preventDefault();
    const respuestaReq = {
      token: this.state.token,
      id: this.state.id,
      respuesta: this.state.selectedOption
    };
    // Cuando el back funcione, cambiar por post
    axios.get(linkForAnswer, respuestaReq)
    .then(res =>{
      console.log(res);
        console.log(res.data.data);
        this.setState({
          resultado: res.data.data.resultado
        })
        if(this.state.resultado === "correcto"){
          console.log(this.state.resultado)
        }
        //console.log(res.resultado)
        //console.log(res.actualUser)
    })
    console.log("You have submitted:", this.state.selectedOption);
  };

  showOptions(options, selectedOption) {
    return options.map(option => (
      <div className="custom-control custom-radio">
        <input
          type="radio"
          id={`default-${option}`}
          name="customRadio"
          className="custom-control-input"
          value={option}
          checked={selectedOption === `${option}`}
          onChange={this.handleOptionChange}
        />
        <label className="custom-control-label" for={`default-${option}`}>
          {option}
        </label>
      </div>
    ));
  }

  render() {
    const usrPosition = [
      this.props.userLocation.lat,
      this.props.userLocation.lng
    ];
    return (
      // this.showPokemons(),
      <Map className="map" center={usrPosition} zoom={this.state.zoom}>
        <TileLayer
          attribution='&amp;copy <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
          url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
        />
        <Marker position={usrPosition} icon={pointerIcon}>
          <Popup>
            Hola {this.state.id}. <br /> Bienvenido, suerte capturando su pokemons.
          </Popup>
        </Marker>
        {this.showPokemons()}
      </Map>
    );
  }
}
export default Mapa;
