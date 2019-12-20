import React, { Component } from "react";

class Timer extends Component {
    constructor(props) {
      super(props);
      this.state = { seconds: 5 };
    }
    
    enable(){ 
        this.props.setDisabled(false)
    }

    disable(){ 
        this.props.setDisabled(true)
    }

    tick() {
      this.setState(state => ({
        seconds: state.seconds - 1
      }));
    }
  
    componentDidMount() {
        this.disable()
      this.interval = setInterval(() =>{
           this.tick()
           if (this.state.seconds === 0) {
               this.enable()
            clearInterval(this.interval)

            } 
        }, 1000);
    }
  
    componentWillUnmount() {
      clearInterval(this.interval);
    }
  
    render() {
      return (
        <div>
          Tiempo restante: {this.state.seconds} s
        </div>
      );
    }
  }
  
  export default Timer;
