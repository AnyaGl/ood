import {Component} from "./Component.js";
import EventType from "./EventType.js";

/**
 * @enum {string}
 */
const MenuItem = {
    ADD_RECTANGLE: "add_rectangle",
    ADD_TRIANGLE: "add_triangle",
    ADD_ELLIPSE: "add_ellipse",
};

class MenuView extends Component{
    constructor() {
        super({
            blockName: "menu",
        });

        /**
         * @type {!Array<!function()>}
         * @private
         */
        this._addRectangleHandlers = [];
        /**
         * @type {!Array<!function()>}
         * @private
         */
        this._addTriangleHandlers = [];
        /**
         * @type {!Array<!function()>}
         * @private
         */
        this._addEllipseHandlers = [];

        /**
         * @type {!Component}
         * @private
         */
        this._addRectangleButton = this._createButton(MenuItem.ADD_RECTANGLE, this._addRectangleHandlers);
        this.addChild(this._addRectangleButton);

        /**
         * @type {!Component}
         * @private
         */
        this._addTriangleButton = this._createButton(MenuItem.ADD_TRIANGLE, this._addTriangleHandlers);
        this.addChild(this._addTriangleButton);

        /**
         * @type {!Component}
         * @private
         */
        this._addEllipseButton = this._createButton(MenuItem.ADD_ELLIPSE, this._addEllipseHandlers);
        this.addChild(this._addEllipseButton);
    }

    /**
     * @param {string} menuItem
     * @param {Array<function()>} handlers
     * @return {!Component}
     * @private
     */
    _createButton(menuItem, handlers) {
        const button = new Component({
            blockName: "add-shape-button",
        });
        button.addClassName(menuItem);

        button.displayObject().addEventListener(EventType.CLICK, () => {
            handlers.forEach(handler => handler());
        });
        return button;
    }

    /**
     * @param {!function()} handler
     */
    doOnAddRectangle(handler) {
        this._addRectangleHandlers.push(handler);
    }

    /**
     * @param {!function()} handler
     */
    doOnAddTriangle(handler) {
        this._addTriangleHandlers.push(handler);
    }

    /**
     * @param {!function()} handler
     */
    doOnAddEllipse(handler) {
        this._addEllipseHandlers.push(handler);
    }
}

export {MenuView}
