class ShapeAppModel {
    /**
     * @param {!Shape} model
     */
    constructor(model) {
        /**
         * @type {!Shape}
         * @private
         */
        this._model = model;
    }

    /**
     * @return {!Shape}
     * @public
     */
    getShape() {
        return this._model;
    }

    /**
     * @return {!Rect}
     * @public
     */
    getFrame() {
        return this._model.getFrame();
    }

    /**
     * @param {!function(!Rect)} handler
     * @public
     */
    doOnFrameChanged(handler) {
        this._model.doOnFrameChanged(handler);
    }
}

export {ShapeAppModel}
