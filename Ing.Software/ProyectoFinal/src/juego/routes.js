// @material-ui/icons

import Person from "@material-ui/icons/Person";

import BubbleChart from "@material-ui/icons/BubbleChart";
import Location from "@material-ui/icons/LocationOn";
import PetsIcon from "@material-ui/icons/Pets";

// core components/views for Admin layout
// import Perfil from "./Perfil.js";
import Perfil from "../views/examples/ProfilePage";
import Ranking from "./Ranking.js";
import Poke from "./Pokedex/layout/Dashboard";
import JuegoPage from "./componentes/juego/JuegoPage";
const dashboardRoutes = [
  {
    path: "/perfil",
    name: "Perfil",
    icon: Person,
    component: Perfil,
    layout: "/game"
  },

  {
    path: "/table",
    name: "Ver Ranking",
    icon: BubbleChart,
    component: Ranking,
    layout: "/game"
  },

  {
    path: "/maps",
    name: "Capturar Pokemon",
    icon: Location,
    component: JuegoPage,
    layout: "/game"
  },
  {
    path: "/pokedex",
    name: "Mis Pokemon",
    icon: PetsIcon,
    component: Poke,
    layout: "/game"
  }
];

export default dashboardRoutes;
