import React, { Component } from "react";
import { MDBRow, MDBCol, MDBInput, MDBBtn } from "mdbreact";
import LoginNavbar from "components/Navbars/LoginNavbar.js";
import AuthService from "./__componentes/AuthService";
// reactstrap components
import "./FormPage.css";
import { Container, Col } from "reactstrap";

// core components

class FormPage extends Component {
  constructor(props) {
    super(props);

    // userService.logout();

    this.state = {
      username: "ozuna",
      password: "12345",
      submitted: false,
      status: false,
      loading: false,
      error: "",
      empresa:"SMP Anime"
    };

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }
  componentDidMount() {
    ///localStorage.clear();
  }

  handleChange(e) {
    const { name, value } = e.target;
    this.setState({ [name]: value });
  }

  handleSubmit(e) {
    
    e.preventDefault();
    const user_credentials = {

      password: this.state.password,
      username: this.state.username,
      empresa: this.state.empresa
    };
    console.log(user_credentials);
    AuthService.login(user_credentials)
     .then( res=>{
      if (res.statusText=== "OK") {
        this.setState({ submitted: true });
        console.log(res.data);
        localStorage.setItem("users", JSON.stringify(res.data));
        console.log(res.data);
        const { from } = { from: { pathname: "/game" } };
        this.props.history.push(from);
      } else {
        this.setState({ error: res.data.message });
        this.setState({ loading: false });
      }
    }).catch(this.state.error);
  }
  render() {
    const { username, password, submitted, loading, error,empresa } = this.state;
    return (
      <>
        <LoginNavbar />
        <div className="page-header clear-filter" filter-color="blue">
          <div
            className="page-header-image"
            style={{
              backgroundImage: "url(" + require("assets/img/fondohd.png") + ")"
            }}
          ></div>
          <div className="content">
            <Container>
              <Col className="ml-auto mr-auto" md="4">
                <form
                  className="needs-validation"
                  onSubmit={this.handleSubmit}
                  noValidate
                >
                  <p className="h5 text-left md-6">SIGN IN</p>
                  <MDBRow>
                    <MDBCol md="6">
                      <div
                        className={
                          "form-group" +
                          (submitted && !username ? " has-error" : "")
                        }
                      >
                        <MDBInput
                          value={username}
                          onChange={this.handleChange}
                          name="username"
                          label="Ingresa tu usuario"
                          icon="user"
                          id="materialFormRegisterNameEx"
                          type="text"
                        >
                          <div className="invalid-feedback">
                            Please provide a valid username
                          </div>
                          <div className="valid-feedback">Looks good!</div>
                        </MDBInput>
                      </div>
                      <MDBInput
                        value={password}
                        onChange={this.handleChange}
                        label="Ingresa tu contraseña"
                        icon="lock"
                        name="password"
                        type="password"
                        required
                        validate={true}
                      >
                       <MDBInput
                        value={empresa}
                        onChange={this.handleChange}
                        label="Ingrese su empresa"
                        icon="building"
                        name="empresa"
                        type="empresa"
                        required
                        validate={true}
                      ></MDBInput>
                        <div className="invalid-feedback">
                          Please provide a valid password
                        </div>
                        <div className="valid-feedback">Looks good!</div>
                      </MDBInput>
                      <div className="text-center">
                        <MDBBtn type="submit" disabled={loading}>
                          Login
                        </MDBBtn>
                      </div>
                    </MDBCol>
                  </MDBRow>
                  {error && <div className={"alert alert-danger"}>{error}</div>}
                </form>
              </Col>
            </Container>
          </div>
        </div>
      </>
    );
  }
}

export default FormPage;
