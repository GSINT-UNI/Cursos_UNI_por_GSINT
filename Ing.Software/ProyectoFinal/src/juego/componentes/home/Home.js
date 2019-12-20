import React from 'react';
 
import Menu from '../menu/Menu'; // Componente Menú 
import Slider from './slider/Slider';
import Servicios from './servicios/Servicios';
import Footer from '../footer/Footer'; // Componente Footer  
 
 
class Home extends React.Component {
 
	render() {
 
		return(
 
			<>
 
			<Menu /> 
 
			<main role="main" className="flex-shrink-0 mt-5">
 
		            <div className="container">
		  	  		
		  	        <Slider /> // Componente Slider 
		  	        <Servicios /> // Componente Servicios
 
		  	        <hr className="featurette-divider" />
 
		            </div>
 
	  		</main>
 
	  		<Footer />
 
	  		</>
 
		)
 
	}
 
}
 
export default Home;