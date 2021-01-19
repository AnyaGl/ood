import {Point} from "../common/Point.js"
import {Rect} from "../common/Rect.js"

class MoveShapeUseCase {
    /**
     * @param {!ShapeAppModel} shape
     */
    constructor(shape) {
        /**
         * @type {!ShapeAppModel}
         * @private
         */
        this._shape = shape;
    }

    /**
     * @param {!Point} from
     * @param {!Point} to
     */
    move(from, to) {
        const deltaX = to.x - from.x;
        const deltaY = to.y - from.y;
        const frame = this._shape.getFrame();
        const newFrame = new Rect({
            leftTop: new Point(frame.leftTop().x + deltaX, frame.leftTop().y + deltaY),
            size: frame.size(),
        });
        this._shape.getShape().setFrame(newFrame);
    }
}

export {MoveShapeUseCase}
