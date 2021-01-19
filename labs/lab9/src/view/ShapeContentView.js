import {Component} from "./Component.js";

/**
 * @extends {Component}
 */
class ShapeContentView extends Component{
    /**
     * @param {string} contentTagName
     */
    constructor(contentTagName) {
        super({
            tagName: "svg",
            elementNS: "http://www.w3.org/2000/svg",
        });
        /**
         * @private {!Element}
         * @const
         */
        this._content = document.createElementNS("http://www.w3.org/2000/svg", contentTagName);
        this.addChild(this._content);

        /** @private {?Rect} */
        this._frame = null;
    }

    /**
     * @param {Rect} frame
     */
    setContentRect(frame) {
        this.setAttribute("width", `${frame.size().width}`);
        this.setAttribute("height", `${frame.size().height}`);
        this.setAttribute("viewBox", `0 0 ${frame.size().width} ${frame.size().height}`);

        this._setContentRectImpl(frame);
        this._frame = frame;
    }

    /**
     * @return {!Element}
     * @protected
     */
    _getContent() {
        return this._content;
    }
}

export {ShapeContentView}
