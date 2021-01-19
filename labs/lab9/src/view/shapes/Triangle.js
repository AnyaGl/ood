import {ShapeContentView} from "../ShapeContentView.js";

/**
 * @extends {ShapeContentView}
 */
class Triangle extends ShapeContentView{
    constructor() {
        super("polygon");
    }

    /** @override */
    _setContentRectImpl(frame) {
        const content = this._getContent();

        const vertexLeftBottom = `0,${frame.size().height}`;
        const vertexMiddleTop = `${frame.size().width / 2},0`;
        const vertexRightBottom = `${frame.size().width},${frame.size().height}`;

        content.setAttribute("points", `${vertexLeftBottom} ${vertexMiddleTop} ${vertexRightBottom}`);
        content.setAttribute("fill", "#907dd5");
    }
}
export {Triangle}
