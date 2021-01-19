import {Component} from "./Component.js";
import {ShapeContentFactory} from "./ShapeContentFactory.js";

class ShapeView extends Component{
    /**
     * @param {!Rect} frame
     * @param {!ShapeType} shapeType
     */
    constructor(frame, shapeType) {
        super({
            blockName: "shape",
        });
        /**
         * @type {!Rect}
         * @private
         */
        this._frame = frame;
        /**
         * @type {?IShapeViewListener}
         * @private
         */
        this._listener = null;

        /**
         * @type {ShapeContentFactory}
         * @private
         */
        this._shapeContentFactory = new ShapeContentFactory();
        /**
         * @type {ShapeContentView}
         * @private
         */
        this._content = this._shapeContentFactory.create(shapeType);

        this.addChild(this._content);

        frame && this.setFrame(frame);
    }

    /**
     * @param {!Rect} frame
     */
    setFrame(frame) {
        this.setX(frame.leftTop().x);
        this.setY(frame.leftTop().y);
        this.setWidth(frame.size().width);
        this.setHeight(frame.size().height);

        this._content.setContentRect(frame);
        this._frame = frame;
    }

    /**
     * @param {!IShapeViewListener} listener
     */
    setListener(listener) {
        this._listener = listener;
    }
}

export {ShapeView}
