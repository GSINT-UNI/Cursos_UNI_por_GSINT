import React from "react";

import { Container } from "reactstrap";
// core components
function IndexHeader() {
  let pageHeader = React.createRef();

  React.useEffect(() => {
    if (window.innerWidth > 991) {
      const updateScroll = () => {
        let windowScrollTop = window.pageYOffset / 3;
        pageHeader.current.style.transform =
          "translate3d(0," + windowScrollTop + "px,0)";
      };
      window.addEventListener("scroll", updateScroll);
      return function cleanup() {
        window.removeEventListener("scroll", updateScroll);
      };
    }
  });

  return (
    <>
      {/* <IndexNavbar /> */}
      <div className="page-header clear-filter" filter-color="blue">
        <div
          className="page-header-image"
          style={{
            backgroundImage: "url(" + require("assets/img/header5.jpg") + ")"
          }}
          ref={pageHeader}
        ></div>
        <Container>
          <div className="content-center brand">
            <img
              alt=".."
              className="n-logo"
              src={require("assets/img/pokeball.svg")}
            ></img>
            <h1 className="h1-seo"> POKEUNI</h1>
            <h3>¿Quieres tener pokemons en tu empresa?</h3>
          </div>
          <h6 className="category category-absolute">
            Designed by Alex-Carlos-Konrad-Luis . Coded by{" "}
            Alex-Carlos-Konrad-Luis .
          </h6>
        </Container>
      </div>
    </>
  );
}

export default IndexHeader;
