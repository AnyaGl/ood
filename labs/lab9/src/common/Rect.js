class Rect {
    /**
     * @param {!Point} leftTop
     * @param {!Size} size
     */
    constructor(leftTop, size) {
        /**
         * {!Point}
         */
        this._leftTop = leftTop;
        /**
         * {!Size}
         */
        this._size = size;
    }

    /**
     * @return {!Point}
     * @public
     */
    leftTop() {
        return this._leftTop;
    }

    /**
     * @return {!Size}
     * @public
     */
    size() {
        return this._size;
    }
}

export {Rect};
