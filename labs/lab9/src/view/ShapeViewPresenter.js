import EventType from "./EventType.js"
import {Point} from "../common/Point.js";

/**
 * @implements {IShapeViewListener}
 */
class ShapeViewPresenter {
    /**
     * @param {!ShapeView} shapeView
     * @param {!ShapeAppModel} shapeAppModel
     * @param {!ShapeSelectionModel} shapeSelectionModel
     */
    constructor(shapeView, shapeAppModel, shapeSelectionModel) {
        /**
         * @type {!ShapeView}
         * @private
         */
        this._shapeView = shapeView;
        /**
         * @type {!ShapeAppModel}
         * @private
         */
        this._shapeAppModel = shapeAppModel;
        /**
         * @type {!ShapeSelectionModel}
         * @private
         */
        this._shapeSelectionModel = shapeSelectionModel;

        this._shapeView.displayObject().addEventListener(EventType.MOUSEDOWN, (event) => {
            this.onMouseDown(event);
        });
        /**
         * @type {?Point}
         * @private
         */
        this._startPoint = null;

        this._mouseMoveHandler = (event) => this.onDrag(event);
        this._mouseUpHandler = (event) => this.onMouseUp(event);
    }

    /** @override */
    onMouseDown(event) {
        event.stopPropagation();
        this._shapeSelectionModel.setSelectedShape(this._shapeAppModel);
        this._startPoint = new Point(event.screenX, event.screenY);

        document.addEventListener('mousemove', this._mouseMoveHandler);
        document.addEventListener('mouseup', this._mouseUpHandler);
    }

    /** @override */
    onMouseUp(event) {
        event.stopPropagation();

        document.removeEventListener('mousemove', this._mouseMoveHandler);
        document.removeEventListener('mouseup', this._mouseUpHandler);
    }

    /** @override */
    onDrag(event) {
        event.stopPropagation();

        const endPoint = new Point(event.screenX, event.screenY);
        const moveShapeUseCase = this._shapeSelectionModel.createMoveShapeUseCase();
        moveShapeUseCase.move(this._startPoint, endPoint);
        this._startPoint = endPoint;

        this._shapeSelectionModel.setSelectedShape(this._shapeAppModel);
    }
}

export {ShapeViewPresenter}
