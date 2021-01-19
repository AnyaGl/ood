/**
 * @interface
 */
class IShapeViewListener {
    /**
     * @param {!Event} event
     */
    onMouseDown(event) {}

    /**
     * @param {!Event} event
     */
    onMouseUp(event) {}

    /**
     * @param {!Event} event
     */
    onDrag(event) {}
}

export {IShapeViewListener}
