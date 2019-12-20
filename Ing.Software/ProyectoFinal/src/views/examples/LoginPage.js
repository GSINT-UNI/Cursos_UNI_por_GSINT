
import React, { Component } from "react";
import {  MDBRow, MDBCol, MDBInput, MDBBtn } from "mdbreact";

// reactstrap components
import {
  Button,
  Card,
  CardHeader,
  CardBody,
  CardFooter,
  Form,
  Input,
  InputGroupAddon,
  InputGroupText,
  InputGroup,
  Container,
  Col
} from "reactstrap";

// core components
import ExamplesNavbar from "components/Navbars/ExamplesNavbar.js";
import TransparentFooter from "components/Footers/TransparentFooter.js";

class LoginPage extends Component {

  constructor(props) {
    super(props);

    // userService.logout();

    this.state = {
      username: "",
      password: "",
      submitted: false,
      loading: false,
      error: ""
    };

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }
  handleChange(e) {
    const { name, value } = e.target;

    this.setState({ [name]: value });
  }

  handleSubmit(e) {
    //e.preventDefault();

    this.setState({ submitted: true });
    const { username, password } = this.state;

    // stop here if form is invalid

    this.setState({ loading: true });
    if (username === "test" && password === "test") {
      this.setState({ submitted: true });

      const { from } = { from: { pathname: "/juego" } };
      this.props.history.push(from);
    } else {
      this.setState({ loading: false });
    }
  }
  render() {
    const { username, password, submitted, loading, error } = this.state;
  return (
    <>
      <ExamplesNavbar />
      <div className="page-header clear-filter" filter-color="blue">
        <div
          className="page-header-image"
          style={{
            backgroundImage: "url(" + require("assets/img/login.jpg") + ")"
          }}
        ></div>
        <div className="content">
          <Container>
            <Col className="ml-auto mr-auto" md="4">
              <Card className="card-login card-plain">
                <Form action="" className="form" method="">

                   <p className="h5 text-left md-6">Sign in</p>
              <MDBRow>
                <MDBCol md="6">
                  <div
                    className={
                      "form-group" + (submitted && !username ? " has-error" : "")
                    }
                  >
                    <MDBInput
                      value={username}
                      onChange={this.handleChange}
                      name="username"
                      label="Type your username"
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
                    label="Type your password"
                    icon="lock"
                    name="password"
                    type="password"
                    required
                    validate={true}
                  >
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
                </Form>
              </Card>
            </Col>
          </Container>
        </div>
        <TransparentFooter />
      </div>
    </>
  );
}
}

export default LoginPage;
