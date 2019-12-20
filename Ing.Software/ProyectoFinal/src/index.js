import React from "react";
import ReactDOM from "react-dom";
import { BrowserRouter, Route, Switch, Redirect } from "react-router-dom";


// styles for this kit
import "assets/css/bootstrap.min.css";
import "assets/scss/now-ui-kit.scss";
import "assets/demo/demo.css";
import "assets/css/mi.css";
import "assets/demo/nucleo-icons-page-styles.css";
import 'leaflet/dist/leaflet.css';
// pages for this kit
import Index from "views/Index.js";
import LoginPage from "login/FormPage.js";
//import LoginPage from "views/examples/LoginPage.js";
import Admin from "juego/Admin"

ReactDOM.render( 
  <BrowserRouter>
    <Switch>
      <Switch>
        <Route path="/index" render={props => <Index {...props} />} />
        <Route
          path="/game"
          render={props => <Admin {...props} />}
        />
        <Route path="/login-page" render={props => <LoginPage {...props} />} />
        <Redirect to="/index" />
        <Redirect from="/" to="/index" />
        </Switch>
    </Switch>
  </BrowserRouter>,
  document.getElementById("root")
);
