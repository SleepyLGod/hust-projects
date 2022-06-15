import store from "."

const actions = {
    addcart({commit}, info) {
      commit('ADDCART', {info});
    },
    deletecart({commit}) {
      commit('DELETECART');
    },
    login({commit}, value) {
      commit('LOGIN', value);
    },
    logout({commit}) {
      commit('LOGOUT');
    }
}

export  default actions