const getters = {
    cartList(state) {
        return state.cartList;
    },
    getSum(state) {
        let sum = 0;
        for (let item of state.cartList) sum += item.checked * item.count;
        return sum;
    },
    getAllPrice(state) {
        let sum = 0;
        for (let item of state.cartList) sum += item.checked * item.count * item.info.price;
        return sum;
    },
    getPlaceList(state) {
        return state.placeList;
    },
    getStorage(state) {
        if (!state.token) 
            state.token = JSON.parse(localStorage.getItem(key));
        return state.token;
    },
    getAddrNum(state) {
        return state.addrNum;
    },
    getOrderNum(state) {
        return state.orderNum;
    },
    getClassNum(state) {
        return state.classNum;
    },
    getScrollNum(state) {
        return state.scrollNum;
    },
    getPlace(state) {
        return state.place;
    }
}

export default getters