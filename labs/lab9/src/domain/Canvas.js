class Canvas {
    constructor() {
        /**
         * @type {!Array<!Shape>}
         * @private
         */
        this._shapes = [];
        /**
         * @type {!Array<!function(!number)>}
         * @private
         */
        this._onShapeAddedHandlers = [];
        /**
         * @type {!Array<!function(!number, !Shape)>}
         * @private
         */
        this._onShapeDeletedHandlers = [];
    }

    /**
     * @return {number}
     * @public
     */
    getShapeCount() {
        return this._shapes.length;
    }

    /**
     * @param {!number} index
     * @return {!Shape|undefined}
     * @public
     */
    getShapeByIndex(index) {
        return this._shapes[index]
    }

    /**
     * @param {!Shape} shape
     * @param {?number} index
     * @public
     */
    insertShape(shape, index) {
        if (index == null)
        {
            this._shapes.push(shape)
        }
        else
        {
            index = index < this._shapes.length ? index : this._shapes.length - 1;
            this._shapes.splice(index, 0, shape);
        }
        this._onShapeAddedHandlers.forEach(handler => handler(index));
    }

    /**
     * @param {!number} index
     * @public
     */
    deleteShape(index) {
        index = index < this._shapes.length ? index : this._shapes.length - 1;
        const shape = this._shapes.splice(index, 1)[0];
        this._onShapeDeletedHandlers.forEach(handler => handler(index, shape));
    }

    /**
     * @param {Shape} shape
     * @return {number}
     * @public
     */
    getIndexByShape(shape)
    {
        for (let i = 0; this.getShapeCount(); ++i)
        {
            if (this.getShapeByIndex(i) == shape)
            {
                return i;
            }
        }
    }

    /**
     * @param {!function(!number)} handler
     * @public
     */
    doOnShapeAdded(handler) {
        this._onShapeAddedHandlers.push(handler);
    }

    /**
     * @param {!function(!number, !Shape)} handler
     * @public
     */
    doOnShapeDeleted(handler) {
        this._onShapeDeletedHandlers.push(handler);
    }
}

export {Canvas}
