#pragma once

const int CURVES_COUNT = 10;


const float MIN_CIRCLE_R = 0.01f;
const float MAX_CIRCLE_R = 10.0f;

const float MIN_ELLIPSE_R1 = 0.01f;
const float MAX_ELLIPSE_R1 = 10.0f;
const float MIN_ELLIPSE_R2 = 0.01f;
const float MAX_ELLIPSE_R2 = 10.0f;

const float MIN_HELIX_R = 0.01f;
const float MAX_HELIX_R = 10.0f;
const float MIN_HELIX_S = 0.01f;
const float MAX_HELIX_S = 10.0f;

enum class CurveType { CIRCLE, ELLIPSE, HELIX };