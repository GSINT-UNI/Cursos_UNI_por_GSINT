import React, { Component } from "react";

import PokemonCard from "./PokemonCard";
import Loading from "../layout/Loading";
//import axios from "axios";

export default class PokemonList extends Component {
  state = {
    // url: "https://pokeapi.co/api/v2/pokemon/?offset=0&limit=151",
    url: "http://api.myjson.com/bins/13hwm4",
    pokemon: null
  };

  async componentDidMount() {
    // const res = await axios.get(this.state.url);
    const res = JSON.parse(localStorage.getItem("users"));
    // this.setState({ pokemon: res.data["results"] });
    this.setState({ pokemon: res.data.user["pokedex"] });
  }

  render() {
    return (
      <div>
        {this.state.pokemon ? (
          <div className="row">
            {this.state.pokemon.map(pokemon => (
              <PokemonCard
                key={pokemon.name}
                name={pokemon.name}
                url={
                  "https://pokeapi.co/api/v2/pokemon/" +
                  pokemon.name.toLowerCase() +
                  "/"
                }
                // url={pokemon.url}
              />
            ))}
          </div>
        ) : (
          <Loading />
        )}
      </div>
    );
  }
}
