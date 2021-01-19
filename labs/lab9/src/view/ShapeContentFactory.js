import {ShapeType} from "../domain/ShapeType.js"
import {Rectangle} from "./shapes/Rectangle.js";
import {Triangle} from "./shapes/Triangle.js";
import {Ellipse} from "./shapes/Ellipse.js";

class ShapeContentFactory {
    create(shapeType) {
        switch (shapeType)
        {
            case ShapeType.RECTANGLE:
                return new Rectangle();
            case ShapeType.TRIANGLE:
                return new Triangle();
            case ShapeType.ELLIPSE:
                return new Ellipse();
            default:
                throw new Error("Unknown shape type!");
        }
    }
}

export {ShapeContentFactory}
