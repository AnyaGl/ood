/**
 * @interface
 */
class IComponent {
    /**
     * @return {!Element}
     */
    displayObject() {}

    /**
     * @param {!Element|!IComponent} child
     * @param {?number} index
     */
    addChild(child, index) {}

    /**
     * @param {!Element|!IComponent} child
     */
    removeChild(child) {}

    /**
     * @param {!Element} child
     * @return {boolean}
     */
    hasChild(child) {}

    /**
     * @param {string} value
     */
    addClassName(value) {}

    /**
     * @param {string} name
     * @param {string} value
     */
    setAttribute(name, value) {}

    /**
     * @param {number} value
     */
    setX(value) {}

    /**
     * @param {number} value
     */
    setY(value) {}

    /**
     * @param {number} value
     */
    setWidth(value) {}

    /**
     * @param {number} value
     */
    setHeight(value) {}
}

export {IComponent}
