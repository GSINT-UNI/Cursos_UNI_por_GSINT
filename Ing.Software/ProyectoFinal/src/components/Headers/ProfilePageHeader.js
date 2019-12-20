import React from "react";

// reactstrap components
import { Container } from "reactstrap";

// core components

function ProfilePageHeader() {
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

  console.log(localStorage.getItem("users"));
  const user_info = JSON.parse(localStorage.getItem("users"));
  var pokemon_capturados = 0;
  var i = 0;

  for (i in user_info.data.user.pokedex) {
    pokemon_capturados += parseInt(user_info.data.pokedex[i].quantity);
    console.log(user_info.data.pokedex[i].quantity);
  }
  return (
    <>
      <div
        className="page-header clear-filter page-header-small"
        filter-color="blue"
      >
        <div
          className="page-header-image"
          style={{
            backgroundImage: "url(" + require("assets/img/fondohd.png") + ")"
          }}
          ref={pageHeader}
        ></div>
        <Container>
          <div className="photo-container">
            {/* <img alt="..." src={user_info.data.urlImagen}></img> */}
            <img alt="..." src={user_info.data.user.user.urlFoto}></img>
          </div>
          {/* <h3 className="title">{user_info.data.username}</h3> */}
          <h3 className="title">{user_info.data.user.user.userName}</h3>
          <br></br>
          <br></br>
          <p className="category">Entrenador Pokemon</p>
          <div className="content">
            <div className="social-description">
              <h2>{pokemon_capturados}</h2>
              <p>Pokemones capturados</p>
            </div>
            <div className="social-description">
              {/* <h2>{user_info.data.totalPoints}</h2> */}
              <h2>{user_info.data.user.user.puntaje}</h2>
              <p>Puntaje acumulado</p>
            </div>
            <div className="social-description">
              <h2>1</h2>
              <p>Puesto en el ranking</p>
            </div>
          </div>
        </Container>
      </div>
    </>
  );
}

export default ProfilePageHeader;
