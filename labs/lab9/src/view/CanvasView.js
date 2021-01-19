import {SelectionFrameView} from "./SelectionFrameView.js";
import {Component} from "./Component.js";
import {ShapeView} from "./ShapeView.js";
import {ShapeViewPresenter} from "./ShapeViewPresenter.js";
import EventType from "./EventType.js";

/**
 * @extends {Component}
 */
class CanvasView extends Component{
    /**
     * @param {!CanvasAppModel} canvasAppModel
     * @param {!ShapeSelectionModel} shapeSelectionModel
     */
    constructor(canvasAppModel, shapeSelectionModel) {
        super({
            blockName: "canvas",
        });
        /**
         * @type {!CanvasAppModel}
         * @private
         */
        this._model = canvasAppModel;
        /**
         * @type {!Array<!ShapeView>}
         * @private
         */
        this._shapes = [];
        /**
         * @type {!ShapeSelectionModel}
         * @private
         */
        this._shapeSelectionModel = shapeSelectionModel;
        this._shapeSelectionModel.doOnSelectionChange((shape) => this.insertSelectionFrame(shape));
        /**
         * @type {?SelectionFrameView}
         * @private
         */
        this._selectionFrame = null;

        canvasAppModel.doOnShapeAdded((index) => this._insertShape(index));
        canvasAppModel.doOnShapeDeleted((index, shape) => this._deleteShape(index, shape));
        this.displayObject().addEventListener(EventType.MOUSEDOWN, () => this.insertSelectionFrame(null));
    }

    /**
     * @param {?ShapeAppModel} shape
     */
    insertSelectionFrame(shape) {
        if (this._selectionFrame)
        {
            this.removeChild(this._selectionFrame);
            this._selectionFrame = null;
        }
        if (shape)
        {
            this._selectionFrame = new SelectionFrameView(shape.getFrame(), this._shapeSelectionModel);
            this.addChild(this._selectionFrame);
        }
        else
        {
            this._shapeSelectionModel.removeSelectedShape();
        }
    }

    /**
     * @param {?number} index
     * @public
     */
    _insertShape(index) {
        if (index == null)
        {
            index = this._model.getShapeCount() - 1;
            const shapeView = this._createShapeView(index);

            this._shapes.push(shapeView)
            this.addChild(shapeView, index);
        }
        else
        {
            index = index < this._shapes.length ? index : this._shapes.length - 1;
            const shapeView = this._createShapeView(index);

            this._shapes.splice(index, 0, shapeView);
            this.addChild(shapeView, index);
        }
    }

    /**
     * @param {number} index
     * @return {ShapeView}
     * @private
     */
    _createShapeView(index) {
        const shapeAppModel = this._model.getShapeByIndex(index);
        const shapeView = new ShapeView(shapeAppModel.getFrame(), shapeAppModel.getShape().getType());

        const shapeViewListener = new ShapeViewPresenter(shapeView, shapeAppModel, this._shapeSelectionModel);
        shapeView.setListener(shapeViewListener);

        shapeAppModel.doOnFrameChanged((frame) => shapeView.setFrame(frame));

        return shapeView;
    }

    /**
     * @param {!number} index
     * @param {!ShapeAppModel} shape
     * @private
     */
    _deleteShape(index, shape) {
        index = index < this._shapes.length ? index : this._shapes.length - 1;
        const shapeView = this._shapes.splice(index, 1)[0];
        this.insertSelectionFrame(null);
        this.removeChild(shapeView.displayObject());
    }
}
export {CanvasView}
