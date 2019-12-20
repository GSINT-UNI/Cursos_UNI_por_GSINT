import axios from "axios";

const RANKING_JSON =
  "http://ec2-18-219-251-98.us-east-2.compute.amazonaws.com/getranking";

class Ranking_service {
  enviar(puestos) {
    return axios.post(RANKING_JSON, puestos);
    //    return axios.get(USER_API_BASE_URL);
  }
}

export default new Ranking_service();
