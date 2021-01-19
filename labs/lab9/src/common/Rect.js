class Rect {
    /** @param {{
     *   leftTop: (!Point),
     *   size: (!Size),
     * }} args
     */
    constructor({leftTop, size}) {
        /**
         * @type {!Point}
         * @private
         */
        this._leftTop = leftTop;
        /**
         * @type {!Size}
         * @private
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
