import {CanvasView} from "./view/CanvasView.js"
import {CanvasAppModel} from "./application/CanvasAppModel.js"
import {Canvas} from "./domain/Canvas.js"
import {Shape} from "./domain/Shape.js"
import {ShapeType} from "./domain/ShapeType.js";
import {Rect} from "./common/Rect.js";
import {Point} from "./common/Point.js";
import {Size} from "./common/Size.js";
import {MenuView} from "./view/MenuView.js";
import {ShapeSelectionModel} from "./application/ShapeSelectionModel.js";

class Application {
    constructor() {
        const appView = document.getElementsByClassName("application")[0];

        const shapeSelectionModel = new ShapeSelectionModel();

        const canvasModel = new Canvas();
        const canvasAppModel = new CanvasAppModel(canvasModel);
        const canvasView = new CanvasView(canvasAppModel, shapeSelectionModel);
        appView.appendChild(canvasView.displayObject());

        const menu = new MenuView();
        appView.appendChild(menu.displayObject());

        menu.doOnAddRectangle(() => canvasModel.insertShape(this._createShape(ShapeType.RECTANGLE)));
        menu.doOnAddTriangle(() => canvasModel.insertShape(this._createShape(ShapeType.TRIANGLE)));
        menu.doOnAddEllipse(() => canvasModel.insertShape(this._createShape(ShapeType.ELLIPSE)));

        document.addEventListener('keydown', (event) => {

            if (event.code == 'Delete')
            {
                const shape = shapeSelectionModel.getSelectedShape();
                if (shape) {
                    canvasModel.deleteShape(canvasModel.getIndexByShape(shape.getShape()));
                }
            }
        });
    }

    /**
     * @param {ShapeType} shapeType
     * @return {Shape}
     */
    _createShape(shapeType) {
        const defaultRect = new Rect({
            leftTop: new Point(0, 0),
            size: new Size(100, 100),
        });
        return new Shape(shapeType, defaultRect);
    }
}

export {Application}
