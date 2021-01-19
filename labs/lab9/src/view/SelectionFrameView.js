import {Component} from "./Component.js";
import CornerType from "./CornerType.js"
import EventType from "./EventType.js"

class SelectionFrameView extends Component{
    /**
     * @param {!Rect} frame
     * @param {!ShapeSelectionModel} model
     */
    constructor(frame, model) {
        super({
            blockName: "selection",
        });
        /**
         * @type {?Rect}
         * @private
         */
        this._setFrame(frame);
        /**
         * @type {!ShapeSelectionModel}
         * @private
         */
        this._model = model;
        model.doOnSelectionFrameChange((frame) => this._setFrame(frame));
        /**
         * @type {!Component}
         * @private
         */
        this._cornerLeftTop = this._createCorner(CornerType.LEFT_TOP);
        this.addChild(this._cornerLeftTop);
        /**
         * @type {!Component}
         * @private
         */
        this._cornerRightTop = this._createCorner(CornerType.RIGHT_TOP);
        this.addChild(this._cornerRightTop);
        /**
         * @type {!Component}
         * @private
         */
        this._cornerRightBottom = this._createCorner(CornerType.RIGHT_BOTTOM);
        this.addChild(this._cornerRightBottom);
        /**
         * @type {!Component}
         * @private
         */
        this._cornerLeftBottom = this._createCorner(CornerType.LEFT_BOTTOM);
        this.addChild(this._cornerLeftBottom);
    }

    /**
     * @param {string} cornerType
     * @return {!Component}
     * @private
     */
    _createCorner(cornerType) {
        const corner = new Component({
            blockName: "corner",
        });
        corner.addClassName(cornerType);

        corner.displayObject().addEventListener(EventType.MOUSEDOWN, (event) => {
            this._model.onCornerMouseDown(event, cornerType, corner);
        });

        return corner;
    }

    /**
     * @param {!Rect} frame
     * @private
     */
    _setFrame(frame) {
        this.setX(frame.leftTop().x);
        this.setY(frame.leftTop().y);
        this.setWidth(frame.size().width);
        this.setHeight(frame.size().height);
    }

}

export {SelectionFrameView}
