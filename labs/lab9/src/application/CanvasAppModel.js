import {ShapeAppModel} from "./ShapeAppModel.js";

class CanvasAppModel {
    /**
     * @param {!Canvas} model
     */
    constructor(model) {
        /**
         * @type {!Canvas}
         * @private
         */
        this._model = model;
        /**
         * @type {!Array<!ShapeAppModel>}
         * @private
         */
        this._shapes = [];
        /**
         * @type {!Array<!function(!number)>}
         * @private
         */
        this._onShapeAddedHandlers = [];
        /**
         * @type {!Array<!function(!number, !ShapeAppModel)>}
         * @private
         */
        this._onShapeDeletedHandlers = [];

        this._model.doOnShapeAdded((index) => {this._insertShape(index)});
        this._model.doOnShapeDeleted((index, shape) => {this._deleteShape(index, shape)});
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
     * @return {!ShapeAppModel|undefined}
     * @public
     */
    getShapeByIndex(index) {
        return this._shapes[index];
    }

    /**
     * @param {!number} index
     * @private
     */
    _insertShape(index) {
        if (index == null)
        {
            const shapeAppModel = new ShapeAppModel(this._model.getShapeByIndex(this._model.getShapeCount() - 1));
            this._shapes.push(shapeAppModel)
        }
        else
        {
            const shapeAppModel = new ShapeAppModel(this._model.getShapeByIndex(index));
            index = index < this._shapes.length ? index : this._shapes.length - 1;
            this._shapes.splice(index, 0, shapeAppModel);
        }
        this._onShapeAddedHandlers.forEach(handler => handler(index));
    }

    /**
     * @param {!number} index
     * @param {!Shape} shape
     * @private
     */
    _deleteShape(index, shape) {
        index = index < this._shapes.length ? index : this._shapes.length - 1;
        const shapeAppModel = this._shapes.splice(index, 1)[0];

        this._onShapeDeletedHandlers.forEach(handler => handler(index, shapeAppModel));
    }

    /**
     * @param {!function(!number)} handler
     * @public
     */
    doOnShapeAdded(handler) {
        this._onShapeAddedHandlers.push(handler);
    }

    /**
     * @param {!function(!number, !ShapeAppModel)} handler
     * @public
     */
    doOnShapeDeleted(handler) {
        this._onShapeDeletedHandlers.push(handler);
    }
}

export {CanvasAppModel}
