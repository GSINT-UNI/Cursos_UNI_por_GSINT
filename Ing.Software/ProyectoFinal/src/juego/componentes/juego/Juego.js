import React from 'react';


import axios from 'axios'

import Mapa from './mapa/Mapa';

//const backendlink = 'https:pokeapi.co/api/v2/pokemon/';
const backendlink = 'https://api.myjson.com/bins/h5mlo';

class Juego extends React.Component {
	state = {
		userLocation: {
			lat: 51.505,
			lng: -0.09,
		},
		zoom: 13,
		pokeData: [],
	}
	componentDidMount() {
		console.log("esperando pos")
		navigator.geolocation.getCurrentPosition((position) => {
			axios.get(backendlink)
				.then(result => {
					const pokeData = result.data.nearest;
					this.setState({ pokeData })
					console.log("axios", pokeData)
				}).catch(console.log)
			console.log("pos obtenida")
			this.setState(
				{
					userLocation: {
						lat: position.coords.latitude,
						lng: position.coords.longitude,
					}
				}
			);
		});

	}

	render() {
		const userLocation = this.state.userLocation;
		const pokeData = this.state.pokeData;
		console.log("render")
		return (
			<>
				<main role="main" className="flex-shrink-0 mt-5">
					<div className="container">
						<Mapa userLocation={userLocation} pokeData={pokeData} />
						<hr className="featurette-divider" />
					</div>
				</main>
			</>

		)

	}

}

export default Juego;
