import {MoveShapeUseCase} from "./MoveShapeUseCase.js";
import {Rect} from "../common/Rect.js";
import {Point} from "../common/Point.js";
import {Size} from "../common/Size.js";
import CornerType from "../view/CornerType.js";

class ShapeSelectionModel {
    constructor() {
        /**
         * @type {?ShapeAppModel}
         * @private
         */
        this._selectedShape = null;
        /**
         * @type {!Array<!function(?ShapeAppModel)>}
         * @private
         */
        this._onSelectionChangeHandlers = [];
        /**
         * @type {!Array<!function(Rect)>}
         * @private
         */
        this._onSelectionFrameChangeHandlers = [];

    }

    doOnSelectionFrameChange(handler) {
        this._onSelectionFrameChangeHandlers.push(handler);
    }
    /**
     * @return {?ShapeAppModel}
     */
    getSelectedShape() {
        return this._selectedShape;
    }

    /**
     * @param {?ShapeAppModel} shape
     */
    setSelectedShape(shape) {
        this._selectedShape = shape;
        this._onSelectionChangeHandlers.forEach(handler => handler(shape));
    }

    /**
     * @public
     */
    removeSelectedShape() {
        this._selectedShape = null;
    }

    /**
     * @param {!function(?ShapeAppModel)} handler
     */
    doOnSelectionChange(handler) {
        this._onSelectionChangeHandlers.push(handler);
    }

    /**
     * @return {?MoveShapeUseCase}
     */
    createMoveShapeUseCase() {
        if (this._selectedShape)
        {
            return new MoveShapeUseCase(this._selectedShape);
        }
        return null;
    }

    /**
     * @param {!MouseEvent} event
     * @param {string} cornerType
     * @param {Component} corner
     * @public
     */
    onCornerMouseDown(event, cornerType, corner) {
        event.stopPropagation();

        let startX = event.screenX;
        let startY = event.screenY;

        this.onStartSelectionResize(startX, startY, cornerType);

        const getDelta = (event) => {
            const deltaX = event.screenX - startX;
            const deltaY = event.screenY - startY;
            startX = event.screenX;
            startY = event.screenY;

            return {deltaX, deltaY};
        };

        const moveHandler = (event) => {
            const {deltaX, deltaY} = getDelta(event);
            this.onSelectionResize(deltaX, deltaY, cornerType);
        };

        const finishHandler = (event) => {
            document.removeEventListener('mousemove', moveHandler);
            document.removeEventListener('mouseup', finishHandler);

            const {deltaX, deltaY} = getDelta(event);
            this.onEndSelectionResize(deltaX, deltaY, cornerType);
        };

        document.addEventListener('mousemove', moveHandler);
        document.addEventListener('mouseup', finishHandler);
    }

    /**
     * @param {number} startX
     * @param {number} startY
     * @param {string} draggedCorner
     * @public
     */
    onStartSelectionResize(startX, startY, draggedCorner) {

    }

    /**
     * @param {number} deltaX
     * @param {number} deltaY
     * @param {string} draggedCorner
     * @public
     */
    onSelectionResize(deltaX, deltaY, draggedCorner) {

        const oldRect = this._selectedShape.getShape().getFrame();
        const newRect = this._calculateNewRect(deltaX, deltaY, draggedCorner, oldRect);

        this._selectedShape.getShape().setFrame(newRect);

        this._onSelectionFrameChangeHandlers.forEach(handler => handler(newRect));

    }
    /**
     * @param {number} deltaX
     * @param {number} deltaY
     * @param {string} draggedCorner
     * @public
     */
    onEndSelectionResize(deltaX, deltaY, draggedCorner) {

    }

    /**
     * @param {number} deltaX
     * @param {number} deltaY
     * @param {string} draggedCorner
     * @param {!Rect} oldRect
     * @return {!Rect}
     * @private
     */
    _calculateNewRect(deltaX, deltaY, draggedCorner, oldRect) {
        const {draggedCornerNewX, draggedCornerNewY} = this._getDraggedCornerNewCoordinate(deltaX, deltaY, draggedCorner, oldRect);
        const {staticCornerX, staticCornerY} = this._getStaticCornerCoordinate(draggedCorner, oldRect);

        return new Rect({
            leftTop: new Point(Math.min(draggedCornerNewX, staticCornerX), Math.min(draggedCornerNewY, staticCornerY)),
            size: new Size(Math.abs(draggedCornerNewX - staticCornerX), Math.abs(draggedCornerNewY - staticCornerY)),
        });
    }

    /**
     * @param {string} draggedCorner
     * @param {!Rect} oldRect
     * @return {{
     *   staticCornerX: number,
     *   staticCornerY: number,
     * }}
     * @private
     */
    _getStaticCornerCoordinate(draggedCorner, oldRect) {
        let staticCornerX;
        let staticCornerY;

        switch (draggedCorner)
        {
            case CornerType.LEFT_TOP:
                staticCornerX = oldRect.leftTop().x + oldRect.size().width;
                staticCornerY = oldRect.leftTop().y + oldRect.size().height;
                break;
            case CornerType.RIGHT_TOP:
                staticCornerX = oldRect.leftTop().x;
                staticCornerY = oldRect.leftTop().y + oldRect.size().height;
                break;
            case CornerType.RIGHT_BOTTOM:
                staticCornerX = oldRect.leftTop().x;
                staticCornerY = oldRect.leftTop().y;
                break;
            case CornerType.LEFT_BOTTOM:
                staticCornerX = oldRect.leftTop().x + oldRect.size().width;
                staticCornerY = oldRect.leftTop().y;
                break;
            default:
                throw new Error("Unknown corner type!");
        }

        return {staticCornerX, staticCornerY};
    }

    /**
     * @param {number} deltaX
     * @param {number} deltaY
     * @param {string} draggedCorner
     * @param {!Rect} oldRect
     * @return {{
     *   draggedCornerNewX: number,
     *   draggedCornerNewY: number,
     * }}
     * @private
     */
    _getDraggedCornerNewCoordinate(deltaX, deltaY, draggedCorner, oldRect) {
        let draggedCornerNewX;
        let draggedCornerNewY;

        switch (draggedCorner)
        {
            case CornerType.LEFT_TOP:
                draggedCornerNewX = oldRect.leftTop().x + deltaX;
                draggedCornerNewY = oldRect.leftTop().y + deltaY;
                break;
            case CornerType.RIGHT_TOP:
                draggedCornerNewX = oldRect.leftTop().x + oldRect.size().width + deltaX;
                draggedCornerNewY = oldRect.leftTop().y + deltaY;
                break;
            case CornerType.RIGHT_BOTTOM:
                draggedCornerNewX = oldRect.leftTop().x + oldRect.size().width + deltaX;
                draggedCornerNewY = oldRect.leftTop().y + oldRect.size().height + deltaY;
                break;
            case CornerType.LEFT_BOTTOM:
                draggedCornerNewX = oldRect.leftTop().x + deltaX;
                draggedCornerNewY = oldRect.leftTop().y + oldRect.size().height + deltaY;
                break;
            default:
                throw new Error("Unknown corner type!");
        }

        return {draggedCornerNewX, draggedCornerNewY};
    }
}


export {ShapeSelectionModel}
