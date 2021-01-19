import {ShapeContentView} from "../ShapeContentView.js";

class Rectangle extends ShapeContentView{
    constructor() {
        super("rect");
    }

    /** @override */
    _setContentRectImpl(frame) {
        const content = this._getContent();

        content.setAttribute("x", "0");
        content.setAttribute("y", "0");
        content.setAttribute("width", `${frame.size().width}`);
        content.setAttribute("height", `${frame.size().height}`);
        content.setAttribute("fill", "#7dd57d");
    }
}
export {Rectangle}
