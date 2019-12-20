import React,{Component} from 'react'
import axios from 'axios'
import background from './images/main.jpg'
import './background.css';
class HomeContainer extends Component{
  /*   backgroundImagePage = () => {
        return (
            <div className="bg">hola</div>
        );
    } */
    
    componentDidMount(){
        axios.get('https:pokeapi.co/api/v2/pokemon/8/')
        .then(result=>{
            console.log(result.data)
        }).catch(console.log)
    }

    render(){
        return( 
            // <div className="bg"></div>
            <div></div>
        )
    }

    
} 
export default HomeContainer

