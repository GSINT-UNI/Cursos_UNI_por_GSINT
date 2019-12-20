import React from "react";
class Menu extends React.Component {
  render() {
    return (
      <nav className="navbar navbar-expand-md navbar-dark fixed-top bg-dark">
        <a className="navbar-brand" href="/perfil">
          Home
        </a>
        <button
          className="navbar-toggler"
          type="button"
          data-toggle="collapse"
          data-target="#navbarCollapse"
          aria-controls="navbarCollapse"
          aria-expanded="true"
          aria-label="Toggle navigation"
        >
          <span className="navbar-toggler-icon"></span>
        </button>
        <div className="collapse navbar-collapse" id="navbarCollapse">
          <ul className="navbar-nav mr-auto">
            <li className="nav-item">
              <a className="nav-link" href="/juego">
                Capturar Pokemon <span className="sr-only">(current)</span>
              </a>
            </li>
            <li className="nav-item">
              <a className="nav-link" href="/pokedex">
                Pokedex
              </a>
            </li>
          </ul>
          <form className="form-inline mt-2 mt-md-0">
            {/* <input className="form-control mr-sm-2" type="text" placeholder="Buscar" aria-label="Buscar"/> */}
            <a className="btn btn-outline-success my-2 my-sm-0" href="/index">
              Salir
            </a>
          </form>
        </div>
      </nav>
    );
  }
}

export default Menu;
