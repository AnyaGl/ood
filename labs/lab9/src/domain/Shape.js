import {generateId} from "../common/Common.js";


class Shape {
    /**
     * @param {!ShapeType} shapeType
     * @param {!Rect} frame
     */
    constructor(shapeType, frame) {
        /**
         * @type {!Rect}
         * @private
         */
        this._frame = frame;
        /**
         * @type {!ShapeType}
         * @private
         */
        this._shapeType = shapeType;
        /**
         * @type {!number}
         * @private
         */
        this._id = generateId();
        /**
         * @type {!Array<!function(!Rect)>}
         * @private
         */
        this._onFrameChangedHandlers = [];
    }

    /**
     * @return {!number}
     * @public
     */
    getId() {
        return this._id;
    }

    /**
     * @return {!Rect}
     * @public
     */
    getFrame() {
        return this._frame;
    }

    /**
     * @param {!Rect} frame
     * @public
     */
    setFrame(frame) {
        this._frame = frame;
        this._onFrameChangedHandlers.forEach(handler => handler(frame));
    }

    /**
     * @return {!ShapeType}
     * @public
     */
    getType() {
        return this._shapeType;
    }

    /**
     * @param {!function(!Rect)} handler
     * @public
     */
    doOnFrameChanged(handler) {
        this._onFrameChangedHandlers.push(handler)
    }
}

export {Shape}
