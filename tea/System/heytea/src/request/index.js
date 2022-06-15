import axios from 'axios';
import store from '/src/store/index.js';

axios.defaults.baseURL = 'http://120.79.152.10:8000';
axios.defaults.timeout = 10000;
axios.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded';

axios.interceptors.request.use(
    config => {
        if (store.state.token) {
            config.headers.Authorization = 'Bearer ' + store.state.token;
        }
        return config;
    },
    error => {
        return Promise.reject(error);
    }
)
axios.interceptors.response.use(
    response =>{
      return response;
    },
    error=>{
      if(error.response){
        switch(error.response.status){
          case 401:
            localStorage.removeItem('token');
            // router.back;
        }
      }
    })

export default axios;