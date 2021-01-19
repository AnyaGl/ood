import {ShapeContentView} from "../ShapeContentView.js";

/**
 * @extends {ShapeContentView}
 */
class Ellipse extends ShapeContentView{
    constructor() {
        super("ellipse");
    }

    /** @override */
    _setContentRectImpl(frame) {
        const content = this._getContent();

        content.setAttribute("cx", `${frame.size().width / 2}`);
        content.setAttribute("cy", `${frame.size().height / 2}`);
        content.setAttribute("rx", `${frame.size().width / 2}`);
        content.setAttribute("ry", `${frame.size().height / 2}`);
        content.setAttribute("fill", "#ec9a5c");
    }
}
export {Ellipse}
